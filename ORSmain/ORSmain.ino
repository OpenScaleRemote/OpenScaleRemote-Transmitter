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
MCP3008 adc1;

//Array für Kanal-Daten
int channelData[16][2] = {};  //potValue, PWMValue

//Array für Moving Average Filter
#define WINDOW_SIZE 10
int mafData[10][5] = {};  //INDEX, VALUE, SUM, READINGS[WINDOW_SIZE], AVERAGED


//########## methods ##########
int readAll() {
  for (i=0; i<16; i++) {
    channelData[i][0] = adc_read();
  }
}

//########## setup code ##########
void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }
  
  adc_init();
  adc_gpio_init(26);
  adc_select_input(0);

  if (!adc1.begin()) {
    Serial.println(F("adc1 hardware is not responding!!"));
    while (1) {
      }
  }
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {
      }
  }
  radio.setPALevel(RF24_PA_LOW);
  radio.setPayloadSize(sizeof(PWMValue));
  radio.openWritingPipe(address[0]);
  radio.stopListening();
}

//########## loop code ##########
void loop() {
  Serial.println(F("Start the loop!"));

  //Daten aus ADC einlesen
  potValue = adc_read();

  //Moving Average Filter
  SUM = SUM - READINGS[INDEX];       // Remove the oldest entry from the sum
  READINGS[INDEX] = potValue;           // Add the newest reading to the window
  SUM = SUM + potValue;                 // Add the newest reading to the sum
  INDEX = (INDEX+1) % WINDOW_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size

  AVERAGED = SUM / WINDOW_SIZE;      // Divide the sum of the window by the window size for the result
  
  //ADC Wert auf PWM Bereich mappen
  PWMValue = map(AVERAGED, 10, 4095, 0, 180);
  
  radio.write(&PWMValue, sizeof(int));
  Serial.println(potValue);
  Serial.println(AVERAGED);
  Serial.println(PWMValue);
  //delay(10);
}
