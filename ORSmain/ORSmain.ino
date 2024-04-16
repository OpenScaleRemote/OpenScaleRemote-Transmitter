//######################################
//########## OpenRemoteSender ##########
//######################################

//########## librarys ##########
#include <SPI.h>
#include "config.h"
#include "Data.h"
#include "SetupMethods.h"
#include "WirelessCommunication.h"
#include "SignalProcessing.h"
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>

//Constructors
SignalProcessing sp;
SetupMethods sm;
WirelessCommunication wc;

//SquareLineUI
/*Change to your screen resolution*/
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

TFT_eSPI tft = TFT_eSPI(screenHeight, screenWidth); /* TFT instance */

//########## setup code ##########
void setup() {
  //GPIO setup
  pinMode(pin_led, OUTPUT);
  sm.setupDigitalPins();
  sm.setupAnalogPins();

  //serial setup
  Serial.begin(115200);
  while (!Serial);
  delay(2000);
  
  //LORA setup
  wc.loraSetup();

  //SqlUI setup
  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

  Serial.println( LVGL_Arduino );
  Serial.println( "I am LVGL_Arduino" );

  lv_init();

  #if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
  #endif

  tft.begin();          /* TFT init */
  tft.setRotation( 1 ); /* Landscape orientation, flipped */
  uint16_t calData[5] = { 392, 3534, 256, 3478, 7 };
  tft.setTouch(calData);


  lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register( &disp_drv );

  /*Initialize the (dummy) input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init( &indev_drv );
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register( &indev_drv );


  ui_init();

  Serial.println( "Setup done" );

  //preparing the index in mafData
  for(int i=0; i<14; i++) {
    mafData[i][0] = 2;
  }
}

//########## loop code ##########
void loop() {
  //blink the onboard led
  digitalWrite(pin_led, blink);
  blink = !blink;

  //read data from adc
  //mapping data from analog range to servo range with limits, zeropoint, deadzone and invert
  sp.processData(mafData, controlData, servoData, channelData);

  //sending data to the radio
  //Serial.println("Sending...");
  while (LoRa.beginPacket() == 0) {
    //Serial.println("waiting for radio ... ");
    //delay(10);
  }
  LoRa.beginPacket();
    if(wc.fastSwitch == false) {
      wc.writeFast1(channelData);
    }else {
      wc.writeFast2(channelData);
    }
  LoRa.endPacket(true);

  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
  //delay(50);

  //debuggingzone
  #ifdef serialData
  for(int i=0; i<1; i++) {
    Serial.print("cD");
    Serial.print(i);
    Serial.print(":");
    //Serial.print(controlData[i][5]);
    Serial.print(channelData[i]);
    //Serial.print(map(analogRead(A0), 0, 1023, 0, 255));
    Serial.print("   ");
  }
  Serial.println();
  delay(10);
  #endif
}

//########## methods ##########
  #if LV_USE_LOG != 0
  /* Serial debugging */
  void my_print(const char * buf)
  {
      Serial.printf(buf);
      Serial.flush();
  }
  #endif

  /* Display flushing */
  void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
  {
      uint32_t w = ( area->x2 - area->x1 + 1 );
      uint32_t h = ( area->y2 - area->y1 + 1 );

      tft.startWrite();
      tft.setAddrWindow( area->x1, area->y1, w, h );
      tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
      tft.endWrite();

      lv_disp_flush_ready( disp );
  }

  /*Read the touchpad*/
  void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
  {
      uint16_t touchX = 0, touchY = 0;

      bool touched = tft.getTouch( &touchX, &touchY, 600 );

      if( !touched )
      {
          data->state = LV_INDEV_STATE_REL;
      }
      else
      {
          data->state = LV_INDEV_STATE_PR;

          /*Set the coordinates*/
          data->point.x = touchX;
          data->point.y = touchY;

          Serial.print( "Data x " );
          Serial.println( touchX );

          Serial.print( "Data y " );
          Serial.println( touchY );
      }
  }