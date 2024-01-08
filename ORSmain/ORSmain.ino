//######################################
//########## OpenRemoteSender ##########
//######################################

//########## librarys ##########
# include <SPI.h>
# include "SignalProcessing.h"
# include <LoRa.h>

//########## objects, arrays, variabeles ##########
bool blink = LOW;

//RFM96W
#define rfm95w_mosi 15
#define rfm95w_miso 12
#define rfm95w_sck 14
#define rfm95w_cs 13
#define rfm95w_reset 20
#define rfm95w_dio0 26

//SignalProcesing
SignalProcessing sp;

struct ServoData {
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
};
ServoData servoData;

//array for moving average filter
#define windowSize 5
int mafData[10][windowSize+2] = {};  // index (0), sum (1), readings[windowSize] (3-windowSize-1)


//########## methods ##########
int mafFiltering(int b, int a) {
  int z;
  mafData[a][1] = mafData[a][1] - mafData[a][mafData[a][0]];        // Remove the oldest entry from the sum
  mafData[a][mafData[a][0]] = b;                                    // Add the newest reading to the window
  mafData[a][1] = mafData[a][1] + b;                                // Add the newest reading to the sum
  mafData[a][0] = mafData[a][0]+1;                                  // Increment the index, and wrap to 0 if it exceeds the window size
  if(mafData[a][0] >= windowSize+2) {
    mafData[a][0] = 2;
  }
  return z = mafData[a][1] / windowSize;                            // Divide the sum of the window by the window size for the result
}

//########## setup code ##########
void setup() {
  //GPIO setup
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);

  //serial setup
  Serial.begin(250000);
  while (!Serial);
  
  Serial.println("LoRa Sender");

  /*//Serial.println("Starting LoRa");
  LoRa.setPins(rfm95w_cs, rfm95w_reset, rfm95w_dio0);
  
  if (!LoRa.begin(915E6)) {
    //Serial.println("Starting LoRa failed!");
    while (1);
  }
  else {
    //Serial.println("Starting LoRa successfull!");
  }*/

  //preparing the index in mafData
  for(int i=0; i<16; i++) {
    mafData[i][0] = 2;
  }
}


//########## loop code ##########
void loop() {
  //blink the onboard led
  digitalWrite(LED_BUILTIN, blink);
  blink = !blink;

  //read data from both adcs
  sp.controlData[0][0] = analogRead(A0);
  sp.controlData[1][0] = analogRead(A1);
  sp.controlData[2][0] = analogRead(A2);
  sp.controlData[3][0] = analogRead(A3);
  sp.controlData[4][0] = analogRead(A4);
  sp.controlData[5][0] = analogRead(A5);
  sp.controlData[6][0] = analogRead(A6);
  sp.controlData[7][0] = analogRead(A7);
  sp.controlData[8][0] = analogRead(A8);
  sp.controlData[9][0] = analogRead(A9);

  //moving average filter
  for(int i=0; i<10; i++) {
    sp.controlData[i][5] = mafFiltering(sp.controlData[i][0], i);
  }

  //mapping data from analog range to servo range with limits, zeropoint, deadzone and invert
  servoData.sD0 = sp.analogLinear(0);
  servoData.sD1 = sp.analogLinear(1);
  servoData.sD2 = sp.analogLinear(2);
  servoData.sD3 = sp.analogLinear(3);
  servoData.sD4 = sp.analogLinear(4);
  servoData.sD5 = sp.analogLinear(5);
  servoData.sD6 = sp.analogLinear(6);
  servoData.sD7 = sp.analogLinear(7);
  servoData.sD8 = sp.analogLinear(8);
  servoData.sD9 = sp.analogLinear(9);
  servoData.sD10 = sp.digital2Way(10, 0);
  servoData.sD11 = sp.digital2Way(11, 1);
  servoData.sD12 = sp.digital2Way(12, 2);
  servoData.sD13 = sp.digital2Way(13, 3);
  servoData.sD14 = sp.digital3Way(14, 4);
  servoData.sD15 = sp.digital3Way(15, 6);
  
  /*//sending data to the radio
  //Serial.println("Sending...");
  while (LoRa.beginPacket() == 0) {
    //Serial.println("waiting for radio ... ");
    delay(10);
  }
  LoRa.beginPacket();
  for (int i = 0; i < sizeof(servoData);i++) {
    // Serial.print(' ');
    LoRa.write(((byte *) &servoData)[i]);
  }
  LoRa.endPacket(true);
  delay(50);*/

  //debuggingzone
  /*for(int i=0; i<16; i++) {
    Serial.print("Channel Data [");
    Serial.print(i);
    Serial.print("][0]: ");
    Serial.println(sp.channelData[i][0]);
  }
  Serial.println("##########");
  for(int i=0; i<10; i++) {
    Serial.print("Control Data [");
    Serial.print(i);
    Serial.print("][0]: ");
    Serial.println(sp.controlData[i][0]);
  }*/
  Serial.println("##########");
  Serial.print("sD0: ");
  Serial.print(servoData.sD0);
  Serial.print(" sD1: ");
  Serial.print(servoData.sD1);
  Serial.print(" sD2: ");
  Serial.print(servoData.sD2);
  Serial.print(" sD3: ");
  Serial.print(servoData.sD3);
  Serial.print(" sD4: ");
  Serial.print(servoData.sD4);
  Serial.print(" sD5: ");
  Serial.print(servoData.sD5);
  Serial.print(" sD6: ");
  Serial.print(servoData.sD6);
  Serial.print(" sD7: ");
  Serial.print(servoData.sD7);
  Serial.print(" sD8: ");
  Serial.print(servoData.sD8);
  Serial.print(" sD9: ");
  Serial.print(servoData.sD9);
  Serial.print(" sD10: ");
  Serial.print(servoData.sD10);
  Serial.print(" sD11: ");
  Serial.print(servoData.sD11);
  Serial.print(" sD12: ");
  Serial.print(servoData.sD12);
  Serial.print(" sD13: ");
  Serial.print(servoData.sD13);
  Serial.print(" sD14: ");
  Serial.print(servoData.sD14);
  Serial.print(" sD15: ");
  Serial.println(servoData.sD15);
  delay(10);
}
