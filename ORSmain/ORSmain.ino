//######################################
//########## OpenRemoteSender ##########
//######################################

//########## librarys ##########
#include "config.h"
#include "SetupMethods.h"
#include <SPI.h>
#include "SignalProcessing.h"

//########## objects, arrays, variabeles ##########
bool blink = LOW;

//Constructors
SignalProcessing sp;
SetupMethods sm;

//########## setup code ##########
void setup() {
  //GPIO setup
  pinMode(LED_BUILTIN, OUTPUT);
  sm.setupAnalogPins();
  sm.setupDigitalPins();

  //serial setup
  Serial.begin(115200);
  while (!Serial);
  delay(2000);
  
  //LORA setup
  sm.loraSetup();

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
  sp.processData();
  
  //sending data to the radio
  //Serial.println("Sending...");
  while (LoRa.beginPacket() == 0) {
    //Serial.println("waiting for radio ... ");
    //delay(10);
  }
  LoRa.beginPacket();
    for (int i = 0; i < 30;i++) {
      // Serial.print(' ');
      LoRa.write(((byte *) &sp.channelData)[i]);
    }
  LoRa.endPacket(true);
  //delay(50);

  //debuggingzone
  #ifdef serialData
  Serial.println("##########");
  Serial.print("sD0: ");
  Serial.print(sp.channelData.sD0);
  Serial.print(" sD1: ");
  Serial.print(sp.channelData.sD1);
  Serial.print(" sD2: ");
  Serial.print(sp.channelData.sD2);
  Serial.print(" sD3: ");
  Serial.print(sp.channelData.sD3);
  Serial.print(" sD4: ");
  Serial.print(sp.channelData.sD4);
  Serial.print(" sD5: ");
  Serial.print(sp.channelData.sD5);
  Serial.print(" sD6: ");
  Serial.print(sp.channelData.sD6);
  Serial.print(" sD7: ");
  Serial.print(sp.channelData.sD7);
  Serial.print(" sD8: ");
  Serial.print(sp.channelData.sD8);
  Serial.print(" sD9: ");
  Serial.print(sp.channelData.sD9);
  Serial.print(" sD10: ");
  Serial.print(sp.channelData.sD10);
  Serial.print(" sD11: ");
  Serial.print(sp.channelData.sD11);
  Serial.print(" sD12: ");
  Serial.print(sp.channelData.sD12);
  Serial.print(" sD13: ");
  Serial.print(sp.channelData.sD13);
  Serial.print(" sD14: ");
  Serial.print(sp.channelData.sD14);
  Serial.print(" sD15: ");
  Serial.println(sp.channelData.sD15);
  delay(10);
  #endif
}