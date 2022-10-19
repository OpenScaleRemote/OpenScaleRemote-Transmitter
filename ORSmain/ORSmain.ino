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

//Array for channel data
//analogInputData, linearMappedData, filteredData, lowerLimit, upperLimit, zeroPoint, deadZone
int channelData[16][7] = {{0,90,90,0,180,90,0},
                          {0,90,90,0,180,90,0},
                          {0,90,90,0,180,90,0},
                          {0,90,90,0,180,90,0},
                          {0,90,90,0,180,90,0},
                          {0,90,90,0,180,90,0},
                          {0,90,90,0,180,90,0},
                          {0,90,90,0,180,90,0},
                          {0,90,90,0,180,90,0},
                          {0,90,90,0,180,90,0},
                          {0,90,90,0,180,90,0},
                          {0,90,90,0,180,90,0},
                          {0,90,90,0,180,90,0},
                          {0,90,90,0,180,90,0},
                          {0,90,90,0,180,90,0},
                          {0,90,90,0,180,90,0}};
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
#define windowSize 10
int mafData[10][windowSize+2] = {};  // index (0), sum (1), readings[windowSize] (3-windowSize-1)


//########## methods ##########
//linearMapping(int input, int lowerLimit, int upperLimit, int zeroLoint, int deadZone)
int linearMapping(int a, int b, int c, int d, int e) {
  int z;
  return z = map(a, 0, 1023, b, c);
}

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
  
  
  
  //preparing the index in mafData
  for(int i=0; i<16; i++) {
    mafData[i][0] = 2;
  }
}


//########## loop code ##########
void loop() {
  //Blink the onboard led
  digitalWrite(25, blink);
  blink = !blink;

  //Read data from both adcs
  for (int i=0; i<8; i++) {
    channelData[i][0] = adc1.analogRead(i);
  }
  for (int i=0; i<2; i++) {
    channelData[i+8][0] = adc2.analogRead(i);
  }

  //Mapping data from analog range to servo range with limits, zeropoint and deadzone
  for(int i=0; i<10; i++) {
    channelData[i][1] = linearMapping(channelData[i][0], channelData[i][3], channelData[i][4], 0, 0);
  }

  //Moving Average Filter
  for(int i=0; i<10; i++) {
    channelData[i][2] = mafFiltering(channelData[i][1], i);
  }

  //Filling the servoData struct
  servoData.sD0 = channelData[0][2];
  servoData.sD1 = channelData[1][2];
  servoData.sD2 = channelData[2][2];
  servoData.sD3 = channelData[3][2];
  servoData.sD4 = channelData[4][2];
  servoData.sD5 = channelData[5][2];
  servoData.sD6 = channelData[6][2];
  servoData.sD7 = channelData[7][2];
  servoData.sD8 = channelData[8][2];
  servoData.sD9 = channelData[9][2];
  servoData.sD10 = channelData[10][2];
  servoData.sD11 = channelData[11][2];
  servoData.sD12 = channelData[12][2];
  servoData.sD13 = channelData[13][2];
  servoData.sD14 = channelData[14][2];
  servoData.sD15 = channelData[15][2];
  
  //Sending data to the radio
  radio.write(&servoData, sizeof(servoData));

  //Debuggingzone
  for(int i=0; i<10; i++) {
    Serial.print("Channel Data [");
    Serial.print(i);
    Serial.print("][2]: ");
    Serial.println(channelData[i][2]);
  }
  Serial.print("sD0: ");
  Serial.print(servoData.sD0);
  Serial.print(" sD1: ");
  Serial.println(servoData.sD1);
  delay(50);
}
