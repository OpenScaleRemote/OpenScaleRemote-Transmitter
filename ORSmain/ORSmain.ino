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
RF24 radio(20, 17);
uint8_t address[][6] = {"00001"};

//MCP3008
MCP3008 adc1;
MCP3008 adc2;

//array for control data
//channelInputData, channelLowerLimit, channelUpperLimit, channelZeroPoint, channelDeadZone, channelFiltered
int controlData[16][6] = {{0,0,1023,511,0,0},
                          {0,0,1023,511,0,0},
                          {0,0,1023,511,0,0},
                          {0,0,1023,511,0,0},
                          {0,0,1023,511,0,0},
                          {0,0,1023,511,0,0},
                          {0,0,1023,511,0,0},
                          {0,0,1023,511,0,0},
                          {0,0,1023,511,0,0},
                          {0,0,1023,511,0,0},
                          {0,0,1023,511,0,0},
                          {0,0,1023,511,0,0},
                          {0,0,1023,511,0,0},
                          {0,0,1023,511,0,0},
                          {0,0,1023,511,0,0},
                          {0,0,1023,511,0,0}};

//array for channel data
//mappedData, servoLowerLimit, servoUpperLimit, servoZeroPoint
int channelData[16][4] = {{90,0,180,90},
                          {90,120,60,90},
                          {90,135,30,90},
                          {90,0,180,90},
                          {90,0,180,90},
                          {90,0,180,90},
                          {90,0,180,90},
                          {90,0,180,90},
                          {90,0,180,90},
                          {90,0,180,90},
                          {90,0,180,90},
                          {90,0,180,90},
                          {90,0,180,90},
                          {90,0,180,90},
                          {90,0,180,90},
                          {90,0,180,90}};
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
int linearConverting(int inPut, int channelLowerLimit, int channelUpperLimit, int channelZeroPoint, int channelDeadZone, int servoLowerLimit, int servoUpperLimit, int servoZeroPoint) {
  if(inPut <= (channelZeroPoint-channelDeadZone)) {
    return map(inPut, channelLowerLimit, (channelZeroPoint-channelDeadZone), servoLowerLimit, (servoZeroPoint-1));
  }else if(inPut >= (channelZeroPoint+channelDeadZone)) {
    return map(inPut, (channelZeroPoint+channelDeadZone), channelUpperLimit, (servoZeroPoint-1), servoUpperLimit);
  }else {
    return servoZeroPoint;
  }
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
  //blink the onboard led
  digitalWrite(25, blink);
  blink = !blink;

  //read data from both adcs
  for (int i=0; i<8; i++) {
    controlData[i][0] = adc1.analogRead(i);
  }
  for (int i=0; i<2; i++) {
    controlData[i+8][0] = adc2.analogRead(i);
  }

  //moving average filter
  for(int i=0; i<10; i++) {
    controlData[i][5] = mafFiltering(controlData[i][0], i);
  }

  //mapping data from analog range to servo range with limits, zeropoint and deadzone
  for(int i=0; i<10; i++) {
    channelData[i][0] = linearConverting(controlData[i][5], controlData[i][1], controlData[i][2], controlData[i][3], controlData[i][4], channelData[i][1], channelData[i][2], channelData[i][3]);
  }

  //read data from 2 phase digital inputs
  for(int i=0; i<4; i++) {
    if(digitalRead(i) == HIGH) {
      channelData[i+10][0] = channelData[i+10][2];
    }else {
      channelData[i+10][0] = channelData[i+10][1];
    }
  }

  //read data from 3 phase digital inputs
  if(digitalRead(4) == HIGH && digitalRead(5) == LOW) {
    channelData[14][0] = channelData[14][2];
  }else if(digitalRead(4) == LOW && digitalRead(5) == HIGH) {
    channelData[14][0] = channelData[14][1];
  }else {
    channelData[14][0] = channelData[14][3];
  }

  if(digitalRead(6) == HIGH && digitalRead(7) == LOW) {
    channelData[15][0] = channelData[15][2];
  }else if(digitalRead(6) == LOW && digitalRead(7) == HIGH) {
    channelData[15][0] = channelData[15][1];
  }else {
    channelData[15][0] = channelData[15][3];
  }
  
  //filling the servoData struct
  servoData.sD0 = channelData[0][0];
  servoData.sD1 = channelData[1][0];
  servoData.sD2 = channelData[2][0];
  servoData.sD3 = channelData[3][0];
  servoData.sD4 = channelData[4][0];
  servoData.sD5 = channelData[5][0];
  servoData.sD6 = channelData[6][0];
  servoData.sD7 = channelData[7][0];
  servoData.sD8 = channelData[8][0];
  servoData.sD9 = channelData[9][0];
  servoData.sD10 = channelData[10][0];
  servoData.sD11 = channelData[11][0];
  servoData.sD12 = channelData[12][0];
  servoData.sD13 = channelData[13][0];
  servoData.sD14 = channelData[14][0];
  servoData.sD15 = channelData[15][0];
  
  //sending data to the radio
  radio.write(&servoData, sizeof(servoData));

  //debuggingzone
  for(int i=0; i<16; i++) {
    Serial.print("Channel Data [");
    Serial.print(i);
    Serial.print("][0]: ");
    Serial.println(channelData[i][0]);
  }
  Serial.println("##########");
  for(int i=0; i<10; i++) {
    Serial.print("Control Data [");
    Serial.print(i);
    Serial.print("][5]: ");
    Serial.println(controlData[i][5]);
  }
  Serial.println("##########");
  /*Serial.print("sD0: ");
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
  Serial.println(servoData.sD9);
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
  Serial.println(servoData.sD15);*/
  //delay(10);
}
