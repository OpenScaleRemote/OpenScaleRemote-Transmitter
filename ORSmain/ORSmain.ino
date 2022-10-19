//######################################
//########## OpenRemoteSender ##########
//######################################

//########## librarys ##########
# include <SPI.h>
# include "printf.h"
# include "RF24.h"
# include <MCP3XXX.h>

//########## objects, arrays, variabeles ##########
bool blink = LOW;

//RF24
RF24 radio(7, 8);
uint8_t address[][6] = {"00001"};

//MCP3008
MCP3008 adc1;
MCP3008 adc2;

//Array für Kanal-Daten
int channelData[16][7] = {};  //analogInputData, linearMappedData, filteredData, lowerLimit, upperLimit, zeroPoint, deadZone
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

//Array für Moving Average Filter
#define WINDOW_SIZE 10
int mafData[10][WINDOW_SIZE+3] = {};  // INDEX (0), VALUE (1), SUM (2), READINGS[WINDOW_SIZE] (3-WINDOW_SIZE-1)

//########## methods ##########
int linearMapping(int a) {
  int b;
  return b = map(a, 0, 1023, 0, 180);
}

int mafFiltering(int a) {
  int b;
  mafData[a][2] = mafData[a][2] - mafData[a][mafData[a][0]];       // Remove the oldest entry from the sum
  mafData[a][mafData[a][0]] = channelData[a][1];                        // Add the newest reading to the window
  mafData[a][2] = mafData[a][2] + channelData[a][1];                 // Add the newest reading to the sum
  mafData[a][0] = mafData[a][0]+1;                              // Increment the index, and wrap to 0 if it exceeds the window size
  if(mafData[a][0] >= WINDOW_SIZE+3) {
    mafData[a][0] = 3;
  }
  return b = mafData[a][2] / WINDOW_SIZE;           // Divide the sum of the window by the window size for the result
}

//########## setup code ##########
void setup() {
  pinMode(25, OUTPUT);
  Serial.begin(115200);
  delay(1000);
  adc1.begin(9);
  adc2.begin(6);
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {
      }
  }
  radio.setPALevel(RF24_PA_LOW);
  radio.setPayloadSize(sizeof(servoData));
  radio.openWritingPipe(address[0]);
  radio.stopListening();

  for(int i=0; i<16; i++) {
    mafData[i][0] = 4;
  }
}

//########## loop code ##########
void loop() {
  digitalWrite(25, blink);
  blink = !blink;

  //Daten aus ADC einlesen
  for (int i=0; i<8; i++) {
    channelData[i][0] = adc1.analogRead(i);
  }
  for (int i=0; i<2; i++) {
    channelData[i+8][0] = adc2.analogRead(i);
  }

  //ADC Wert auf PWM Bereich mappen
  for(int i=0; i<2; i++) {
    channelData[i][1] = linearMapping(channelData[i][0]);
  }

  //Moving Average Filter
  for(int i=0; i<2; i++) {
    mafFiltering(i);
  }

  servoData.sD0 = mafData[0][3];
  servoData.sD1 = mafData[1][3];
  
  radio.write(&servoData, sizeof(servoData));

  for(int i=0; i<10; i++) {
    Serial.print("Channel Data [");
    Serial.print(i);
    Serial.print("]: ");
    Serial.println(channelData[i][0]);
  }
  Serial.print("sD0: ");
  Serial.print(servoData.sD0);
  Serial.print(" sD1: ");
  Serial.println(servoData.sD1);
//  delay(50);
}
