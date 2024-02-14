//######################################
//########## OpenRemoteSender ##########
//######################################

//########## librarys ##########
# include "config.h"
# include <SPI.h>
# include "SignalProcessing.h"
# include <LoRa.h>

//########## objects, arrays, variabeles ##########
bool blink = LOW;

//SignalProcesing
SignalProcessing sp;

struct channelData {
  byte sD0=0;
  byte sD1=0;
  byte sD2=0;
  byte sD3=0;
  byte sD4=0;
  byte sD5=0;
  byte sD6=0;
  byte sD7=0;
  byte sD8=0;
  byte sD9=0;
  byte sD10=0;
  byte sD11=0;
  byte sD12=0;
  byte sD13=0;
  byte sD14=0;
  byte sD15=0;
  byte sD16=0;
  byte sD17=0;
  byte sD18=0;
  byte sD19=0;
  byte sD20=0;
  byte sD21=0;
  byte sD22=0;
  byte sD23=0;
  byte sD24=0;
  byte sD25=0;
  byte sD26=0;
  byte sD27=0;
  byte sD28=0;
  byte sD29=0;
};
channelData channelData;

//########## setup code ##########
void setup() {
  //GPIO setup
  pinMode(LED_BUILTIN, OUTPUT);

  #ifdef ch0_active
    pinMode(A0, INPUT);
  #endif

  #ifdef ch1_active
    pinMode(A1, INPUT);
  #endif

  #ifdef ch2_active
    pinMode(A2, INPUT);
  #endif

  #ifdef ch3_active
    pinMode(A3, INPUT);
  #endif

  #ifdef ch4_active
    pinMode(A4, INPUT);
  #endif

  #ifdef ch5_active
    pinMode(A5, INPUT);
  #endif

  #ifdef ch6_active
    pinMode(A6, INPUT);
  #endif

  #ifdef ch7_active
    pinMode(A7, INPUT);
  #endif

  #ifdef ch8_active
    pinMode(A8, INPUT);
  #endif

  #ifdef ch9_active
    pinMode(A9, INPUT);
  #endif

  #ifdef ch10_active
    pinMode(A10, INPUT);
  #endif

  #ifdef ch11_active
    pinMode(A11, INPUT);
  #endif

  #ifdef ch12_active
    pinMode(A12, INPUT);
  #endif

  #ifdef ch13_active
    pinMode(A13, INPUT);
  #endif

  //serial setup
  Serial.begin(115200);
  while (!Serial);
  
  Serial.println("LoRa Sender");

  Serial.println("Starting LoRa");
  LoRa.setPins(rfm95w_cs, rfm95w_reset, rfm95w_dio0);
  
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  else {
    Serial.println("Starting LoRa successfull!");
  }

  //preparing the index in mafData
  for(int i=0; i<14; i++) {
    sp.mafData[i][0] = 2;
  }
}


//########## loop code ##########
void loop() {
  //blink the onboard led
  digitalWrite(LED_BUILTIN, blink);
  blink = !blink;

  //read data from adc
  //mapping data from analog range to servo range with limits, zeropoint, deadzone and invert
  #ifdef ch0_active
    sp.controlData[0][0] = analogRead(A0);
    sp.controlData[0][5] = sp.mafFiltering(sp.controlData[0][0], 0);
    #ifdef ch0_analogLinear
      channelData.sD0 = sp.analogLinear(0);
    #endif
  #endif

  #ifdef ch1_active
    sp.controlData[1][0] = analogRead(A1);
    sp.controlData[1][5] = sp.mafFiltering(sp.controlData[1][0], 1);
    #ifdef ch1_analogLinear
      channelData.sD1 = sp.analogLinear(1);
    #endif
  #endif

  #ifdef ch2_active
    sp.controlData[2][0] = analogRead(A2);
    sp.controlData[2][5] = sp.mafFiltering(sp.controlData[2][0], 2);
    #ifdef ch2_analogLinear
      channelData.sD2 = sp.analogLinear(2);
    #endif
  #endif

  #ifdef ch3_active
    sp.controlData[3][0] = analogRead(A3);
    sp.controlData[3][5] = sp.mafFiltering(sp.controlData[3][0], 3);
    #ifdef ch3_analogLinear
      channelData.sD3 = sp.analogLinear(3);
    #endif
  #endif

  #ifdef ch4_active
    sp.controlData[4][0] = analogRead(A4);
    sp.controlData[4][5] = sp.mafFiltering(sp.controlData[4][0], 4);
    #ifdef ch4_analogLinear
      channelData.sD4 = sp.analogLinear(4);
    #endif
  #endif

  #ifdef ch5_active
    sp.controlData[5][0] = analogRead(A5);
    sp.controlData[5][5] = sp.mafFiltering(sp.controlData[5][0], 5);
    #ifdef ch5_analogLinear
      channelData.sD5 = sp.analogLinear(5);
    #endif
  #endif

  #ifdef ch6_active
    sp.controlData[6][0] = analogRead(A6);
    sp.controlData[6][5] = sp.mafFiltering(sp.controlData[6][0], 6);
    #ifdef ch6_analogLinear
      channelData.sD6 = sp.analogLinear(6);
    #endif
  #endif

  #ifdef ch7_active
    sp.controlData[7][0] = analogRead(A7);
    sp.controlData[7][5] = sp.mafFiltering(sp.controlData[7][0], 7);
    #ifdef ch7_analogLinear
      channelData.sD7 = sp.analogLinear(7);
    #endif
  #endif

  #ifdef ch8_active
    sp.controlData[8][0] = analogRead(A8);
    sp.controlData[8][5] = sp.mafFiltering(sp.controlData[8][0], 8);
    #ifdef ch8_analogLinear
      channelData.sD8 = sp.analogLinear(8);
    #endif
  #endif

  #ifdef ch9_active
    sp.controlData[9][0] = analogRead(A9);
    sp.controlData[9][5] = sp.mafFiltering(sp.controlData[9][0], 9);
    #ifdef ch9_analogLinear
      channelData.sD9 = sp.analogLinear(9);
    #endif
  #endif

  #ifdef ch10_active
    sp.controlData1[0][0] = analogRead(A10);
    sp.controlData[10][5] = sp.mafFiltering(sp.controlData[10][0], 10);
    #ifdef ch11_analogLinear
      channelData.sD10 = sp.analogLinear(10);
    #endif
  #endif

  #ifdef ch11_active
    sp.controlData[11][0] = analogRead(A11);
    sp.controlData[11][5] = sp.mafFiltering(sp.controlData[11][0], 11);
    #ifdef ch11_analogLinear
      channelData.sD11 = sp.analogLinear(11);
    #endif
  #endif

  #ifdef ch12_active
    sp.controlData[12][0] = analogRead(A12);
    sp.controlData[12][5] = sp.mafFiltering(sp.controlData[12][0], 12);
    #ifdef ch12_analogLinear
      channelData.sD12 = sp.analogLinear(12);
    #endif
  #endif

  #ifdef ch13_active
    sp.controlData[13][0] = analogRead(A13);
    sp.controlData[13][5] = sp.mafFiltering(sp.controlData[13][0], 13);
    #ifdef ch13_analogLinear
      channelData.sD13 = sp.analogLinear(13);
    #endif
  #endif

  #ifdef ch14_active
    #ifdef ch14_digital2Way
      channelData.sD14 = sp.digital2Way(14, 0);
    #endif
    #ifdef ch14_digital3Way
      channelData.sD14 = sp.digital3Way(14, 0);
    #endif
  #endif

  #ifdef ch15_active
    #ifdef ch15_digital2Way
      channelData.sD15 = sp.digital2Way(15, 0);
    #endif
  #endif

  #ifdef ch16_active
    #ifdef ch16_digital2Way
      channelData.sD16 = sp.digital2Way(16, 0);
    #endif
    #ifdef ch16_digital3Way
      channelData.sD16 = sp.digital3Way(16, 0);
    #endif
  #endif

  #ifdef ch17_active
    #ifdef ch17_digital2Way
      channelData.sD17 = sp.digital2Way(17, 0);
    #endif
  #endif

  #ifdef ch18_active
    #ifdef ch18_digital2Way
      channelData.sD18 = sp.digital2Way(18, 0);
    #endif
    #ifdef ch18_digital3Way
      channelData.sD18 = sp.digital3Way(18, 0);
    #endif
  #endif

  #ifdef ch19_active
    #ifdef ch19_digital2Way
      channelData.sD19 = sp.digital2Way(19, 0);
    #endif
  #endif

  #ifdef ch20_active
    #ifdef ch20_digital2Way
      channelData.sD20 = sp.digital2Way(20, 0);
    #endif
    #ifdef ch20_digital3Way
      channelData.sD20 = sp.digital3Way(20, 0);
    #endif
  #endif

  #ifdef ch21_active
    #ifdef ch21_digital2Way
      channelData.sD21 = sp.digital2Way(21, 0);
    #endif
  #endif

  #ifdef ch22_active
    #ifdef ch22_digital2Way
      channelData.sD22 = sp.digital2Way(22, 0);
    #endif
  #endif

  #ifdef ch23_active
    #ifdef ch23_digital2Way
      channelData.sD23 = sp.digital2Way(23, 0);
    #endif
  #endif

  #ifdef ch24_active
    #ifdef ch24_digital2Way
      channelData.sD24 = sp.digital2Way(24, 0);
    #endif
  #endif

  #ifdef ch25_active
    #ifdef ch25_digital2Way
      channelData.sD25 = sp.digital2Way(25, 0);
    #endif
  #endif

  #ifdef ch26_active
    #ifdef ch26_digital2Way
      channelData.sD26 = sp.digital2Way(26, 0);
    #endif
  #endif

  #ifdef ch27_active
    #ifdef ch27_digital2Way
      channelData.sD27 = sp.digital2Way(27, 0);
    #endif
  #endif

  #ifdef ch28_active
    #ifdef ch28_digital2Way
      channelData.sD28 = sp.digital2Way(28, 0);
    #endif
  #endif

  #ifdef ch29_active
    #ifdef ch29_digital2Way
      channelData.sD29 = sp.digital2Way(29, 0);
    #endif
  #endif
  
  /*//sending data to the radio
  //Serial.println("Sending...");
  while (LoRa.beginPacket() == 0) {
    //Serial.println("waiting for radio ... ");
    delay(10);
  }
  LoRa.beginPacket();
  for (int i = 0; i < sizeof(channelData);i++) {
    // Serial.print(' ');
    LoRa.write(((byte *) &channelData)[i]);
  }
  LoRa.endPacket(true);
  delay(50);*/

  //debuggingzone
  #ifdef serialData
  for(int i=0; i<16; i++) {
    Serial.print("Channel Data [");
    Serial.print(i);
    Serial.print("][0]: ");
    Serial.println(sp.servoData[i][0]);
  }
  Serial.println("##########");
  for(int i=0; i<10; i++) {
    Serial.print("Control Data [");
    Serial.print(i);
    Serial.print("][0]: ");
    Serial.println(sp.controlData[i][0]);
  }
  Serial.println("##########");
  Serial.print("sD0: ");
  Serial.print(channelData.sD0);
  Serial.print(" sD1: ");
  Serial.print(channelData.sD1);
  Serial.print(" sD2: ");
  Serial.print(channelData.sD2);
  Serial.print(" sD3: ");
  Serial.print(channelData.sD3);
  Serial.print(" sD4: ");
  Serial.print(channelData.sD4);
  Serial.print(" sD5: ");
  Serial.print(channelData.sD5);
  Serial.print(" sD6: ");
  Serial.print(channelData.sD6);
  Serial.print(" sD7: ");
  Serial.print(channelData.sD7);
  Serial.print(" sD8: ");
  Serial.print(channelData.sD8);
  Serial.print(" sD9: ");
  Serial.print(channelData.sD9);
  Serial.print(" sD10: ");
  Serial.print(channelData.sD10);
  Serial.print(" sD11: ");
  Serial.print(channelData.sD11);
  Serial.print(" sD12: ");
  Serial.print(channelData.sD12);
  Serial.print(" sD13: ");
  Serial.print(channelData.sD13);
  Serial.print(" sD14: ");
  Serial.print(channelData.sD14);
  Serial.print(" sD15: ");
  Serial.println(channelData.sD15);
  delay(10);
}
#endif