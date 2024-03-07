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
#include "IO_PCF8575.h"

//Constructors
SignalProcessing sp;
SetupMethods sm;
WirelessCommunication wc;
PCF8575 pcf8575;

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

  //PCF8575 setup
  pcf8575.pcf8575setup();

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

  //read data
  sp.readInternalADC(controlData);
  pcf8575.readpcf8575(controlData);

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
  //delay(50);

  //debuggingzone
  #ifdef serialData
  for(int i=0; i<2; i++) {
    Serial.print("cD");
    Serial.print(i);
    Serial.print(":");
    Serial.print(controlData[i][5]);
    //Serial.print(channelData[i]);
    //Serial.print(map(analogRead(A0), 0, 1023, 0, 255));
    Serial.print("   ");
  }
  Serial.println();
  delay(10);
  #endif
}