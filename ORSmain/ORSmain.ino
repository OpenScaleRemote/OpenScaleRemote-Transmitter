//######################################
//########## OpenRemoteSender ##########
//######################################

//########## librarys ##########
# include "SPI.h"
# include "printf.h"
# include "RF24.h"
# include "MCP3XXX.h"
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
int counter = 0;

//RF24
//RF24 radio(20, 17);
//uint8_t address[][6] = {"00001"};

//MCP3008
MCP3008 adc1;
MCP3008 adc2;

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
  pinMode(25, OUTPUT);
  pinMode(0, INPUT_PULLDOWN);
  pinMode(1, INPUT_PULLDOWN);
  pinMode(2, INPUT_PULLDOWN);
  pinMode(3, INPUT_PULLDOWN);
  pinMode(4, INPUT_PULLDOWN);
  pinMode(5, INPUT_PULLDOWN);
  pinMode(6, INPUT_PULLDOWN);
  pinMode(7, INPUT_PULLDOWN);

  //serial setup
  Serial.begin(115200);
  delay(1000);
  adc1.begin(21);
  adc2.begin(22);
  Serial.println("LoRa Sender");
  LoRa.setPins(rfm95w_cs, rfm95w_reset, 2);
  LoRa.setSPI(SPI1);
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  else {
    Serial.println("Starting LoRa successfull!");
  }

  //preparing the index in mafData
  for(int i=0; i<16; i++) {
    mafData[i][0] = 2;
  }
}


//########## loop code ##########
void loop() {
  //blink the onboard led
  digitalWrite(25, blink);
  blink = !blink;

  //read data from both adcs
  for (int i=0; i<8; i++) {
    sp.controlData[i][0] = adc1.analogRead(i);
  }
  for (int i=0; i<2; i++) {
    sp.controlData[i+8][0] = adc2.analogRead(i);
  }

  //moving average filter
  for(int i=0; i<10; i++) {
    sp.controlData[i][5] = mafFiltering(sp.controlData[i][0], i);
  }

  //mapping data from analog range to servo range with limits, zeropoint, deadzone and invert
  //servoData.sD0 = sp.analogLinear(0);
  servoData.sD1 = sp.analogLinear(1);
  servoData.sD2 = sp.analogLinear(2);
  //servoData.sD3 = sp.analogLinear(3);
  //servoData.sD4 = sp.analogLinear(4);
  //servoData.sD5 = sp.analogLinear(5);
  //servoData.sD6 = sp.analogLinear(6);
  //servoData.sD7 = sp.analogLinear(7);
  //servoData.sD8 = sp.analogLinear(8);
  //servoData.sD9 = sp.analogLinear(9);
  //servoData.sD10 = sp.digital2Way(10, 0);
  //servoData.sD11 = sp.digital2Way(11, 1);
  //servoData.sD12 = sp.digital2Way(12, 2);
  //servoData.sD13 = sp.digital2Way(13, 3);
  //servoData.sD14 = sp.digital3Way(14, 4);
  //servoData.sD15 = sp.digital3Way(15, 6);
  
  //sending data to the radio
  LoRa.beginPacket();
  LoRa.write(servoData, sizeof(servoData));
  LoRa.endPacket();

  //debuggingzone
  /*for(int i=0; i<16; i++) {
    Serial.print("Channel Data [");
    Serial.print(i);
    Serial.print("][0]: ");
    Serial.println(sp.channelData[i][0]);
  }*/
  Serial.println("##########");
  for(int i=0; i<10; i++) {
    Serial.print("Control Data [");
    Serial.print(i);
    Serial.print("][5]: ");
    Serial.println(sp.controlData[i][5]);
  }
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
  //delay(10);
}
