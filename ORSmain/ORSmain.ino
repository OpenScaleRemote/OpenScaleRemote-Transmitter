//######################################
//########## OpenRemoteSender ##########
//######################################

//########## librarys ##########
# include <SPI.h>
# include "printf.h"
# include "RF24.h"
# include <MCP3XXX.h>

//########## objects, arrays, variabeles ##########
//RF24
RF24 radio(7, 8);
uint8_t address[][6] = {"00001"};

//MCP3008
//MCP3008 adc1;

//Array für Kanal-Daten
int inputData[16] = {};
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
// #define WINDOW_SIZE 10
// int mafData[10][5] = {};  //INDEX, VALUE, SUM, READINGS[WINDOW_SIZE], AVERAGED


//########## methods ##########
void readAll(int a) {
  for (int i=0; i<a; i++) {
    adc_select_input(i);
    inputData[i] = adc_read();
  }
}

void linearMapping() {
  servoData.sD0 = map(inputData[0], 0, 4095, 0, 180);
  servoData.sD1 = map(inputData[1], 0, 4095, 0, 180);
}

//########## setup code ##########
void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }
  
  adc_init();
  adc_gpio_init(26);
  adc_gpio_init(27);
//  adc_select_input(0);

//  if (!adc1.begin()) {
//    Serial.println(F("adc1 hardware is not responding!!"));
//    while (1) {
//      }
//  }
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {
      }
  }
  radio.setPALevel(RF24_PA_LOW);
  radio.setPayloadSize(sizeof(servoData));
  radio.openWritingPipe(address[0]);
  radio.stopListening();
}

//########## loop code ##########
void loop() {
  Serial.println(F("Start the loop!"));

  //Daten aus ADC einlesen
  readAll(2);

//  //Moving Average Filter
//  SUM = SUM - READINGS[INDEX];       // Remove the oldest entry from the sum
//  READINGS[INDEX] = potValue;           // Add the newest reading to the window
//  SUM = SUM + potValue;                 // Add the newest reading to the sum
//  INDEX = (INDEX+1) % WINDOW_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size

//  AVERAGED = SUM / WINDOW_SIZE;      // Divide the sum of the window by the window size for the result
  
  //ADC Wert auf PWM Bereich mappen
  linearMapping();
  
  radio.write(&servoData, sizeof(servoData));
//  Serial.println(AVERAGED);
  Serial.print("sD0: ");
  Serial.print(servoData.sD0);
  Serial.print(" sD1: ");
  Serial.println(servoData.sD1);
  //delay(10);
}
