#include "SignalProcessing.h"

void SignalProcessing::readInternalADC(int arrayControlData[30][6]) {
  #ifdef ch0_active
    arrayControlData[0][0] = analogRead(pin_ch0);
  #endif

  #ifdef ch1_active
    arrayControlData[1][0] = analogRead(pin_ch1);
  #endif

  #ifdef ch2_active
    arrayControlData[2][0] = analogRead(pin_ch2);
  #endif

  #ifdef ch3_active
    arrayControlData[3][0] = analogRead(pin_ch3);
  #endif

  #ifdef ch4_active
    arrayControlData[4][0] = analogRead(pin_ch4);
  #endif

  #ifdef ch5_active
    arrayControlData[5][0] = analogRead(pin_ch5);
  #endif

  #ifdef ch6_active
    arrayControlData[6][0] = analogRead(pin_ch6);
  #endif

  #ifdef ch7_active
    arrayControlData[7][0] = analogRead(pin_ch7);
  #endif

  #ifdef ch8_active
    arrayControlData[8][0] = analogRead(pin_ch8);
  #endif

  #ifdef ch9_active
    arrayControlData[9][0] = analogRead(pin_ch9);
  #endif

  #ifdef ch10_active
    arrayControlData[10][0] = analogRead(pin_ch10);
  #endif

  #ifdef ch11_active
    arrayControlData[11][0] = analogRead(pin_ch11);
  #endif

  #ifdef ch12_active
    arrayControlData[12][0] = analogRead(pin_ch12);
  #endif

  #ifdef ch13_active
    arrayControlData[13][0] = analogRead(pin_ch13);
  #endif
}



int SignalProcessing::mafFiltering(int chNum, int sensorValue, int arrayMafData[14][2+windowSize]) {                     // index (0), sum (1), readings(2 bis 1+windowSize)
  int z;
  arrayMafData[chNum][1] = arrayMafData[chNum][1] - arrayMafData[chNum][arrayMafData[chNum][0]];        // Remove the oldest entry from the sum
  arrayMafData[chNum][arrayMafData[chNum][0]] = sensorValue;                                                      // Add the newest reading to the window
  arrayMafData[chNum][1] = arrayMafData[chNum][1] + sensorValue;                                                    // Add the newest reading to the sum
  arrayMafData[chNum][0] = arrayMafData[chNum][0]+1;                                                                // Increment the index, and wrap to 0 if it exceeds the window size
  if(arrayMafData[chNum][0] >= 7) {
    arrayMafData[chNum][0] = 2;
  }
  return z = arrayMafData[chNum][1] / windowSize;                                                                          // Divide the sum of the window by the window size for the result
}



int SignalProcessing::analogLinear(int inputChannel, int arrayControlData[30][6], int arrayServoData[30][4]) {
  switch(arrayServoData[inputChannel][3]) {
    case 0:
      if(arrayControlData[inputChannel][5] < (arrayControlData[inputChannel][3]-arrayControlData[inputChannel][4])) {
        return map(arrayControlData[inputChannel][5], arrayControlData[inputChannel][1], (arrayControlData[inputChannel][3]-arrayControlData[inputChannel][4]), arrayServoData[inputChannel][0], (arrayServoData[inputChannel][2]-1));
      }else if(arrayControlData[inputChannel][5] > (arrayControlData[inputChannel][3]+arrayControlData[inputChannel][4])) {
        return map(arrayControlData[inputChannel][5], (arrayControlData[inputChannel][3]+arrayControlData[inputChannel][4]), arrayControlData[inputChannel][2], (arrayServoData[inputChannel][2]-1), arrayServoData[inputChannel][1]);
      }else {
        return arrayServoData[inputChannel][2];
      }
      break;
    case 1:
      if(arrayControlData[inputChannel][5] < (arrayControlData[inputChannel][3]-arrayControlData[inputChannel][4])) {
        return map(arrayControlData[inputChannel][5], arrayControlData[inputChannel][1], (arrayControlData[inputChannel][3]-arrayControlData[inputChannel][4]), arrayServoData[inputChannel][1], (arrayServoData[inputChannel][2]+1));
      }else if(arrayControlData[inputChannel][5] > (arrayControlData[inputChannel][3]+arrayControlData[inputChannel][4])) {
        return map(arrayControlData[inputChannel][5], (arrayControlData[inputChannel][3]+arrayControlData[inputChannel][4]), arrayControlData[inputChannel][2], (arrayServoData[inputChannel][2]-1), arrayServoData[inputChannel][0]);
      }else {
        return arrayServoData[inputChannel][2];
      }
      break;
    default:
      Serial.print("Falscher Wert Servoinvertierung Kanal: ");
      Serial.println(inputChannel);
      return 90;
  }
}



int SignalProcessing::digital2Way(int inputChannel, int inputChannelPin, int arrayServoData[30][4]) {
  switch(arrayServoData[inputChannel][3]) {
    case 0:
      if(digitalRead(inputChannelPin) == 0) {
        return arrayServoData[inputChannel][1];
      }else {
        return arrayServoData[inputChannel][0];
      }
      break;
    case 1:
      if(digitalRead(inputChannelPin) == 0) {
        return arrayServoData[inputChannel][0];
      }else {
        return arrayServoData[inputChannel][1];
      }
      break;
    default:
      Serial.print("Falscher Wert Servoinvertierung Kanal: ");
      Serial.println(inputChannel);
      return 90;
  }
}
  


int SignalProcessing::digital3Way(int inputChannel, int inputChannelPin, int arrayServoData[30][4]) {
  switch(arrayServoData[inputChannel][3]) {
    case 0:
      if(digitalRead(inputChannelPin) == HIGH && digitalRead(inputChannelPin+1) == LOW) {
        return arrayServoData[inputChannel][1];
      }else if(digitalRead(inputChannelPin) == LOW && digitalRead(inputChannelPin+1) == HIGH) {
        return arrayServoData[inputChannel][0];
      }else {
        return arrayServoData[inputChannel][2];
      }
      break;
    case 1:
      if(digitalRead(inputChannelPin) == HIGH && digitalRead(inputChannelPin+1) == LOW) {
        return arrayServoData[inputChannel][0];
      }else if(digitalRead(inputChannelPin) == LOW && digitalRead(inputChannelPin+1) == HIGH) {
        return arrayServoData[inputChannel][1];
      }else {
        return arrayServoData[inputChannel][2];
      }
      break;
    default:
      Serial.print("Falscher Wert Servoinvertierung Kanal: ");
      Serial.println(inputChannel);
      return 90;
  }
}



void SignalProcessing::processData(int arrayMafData[14][2+windowSize], int arrayControlData[30][6], int arrayServoData[30][4], byte arrayChannelData[30]) {
  #ifdef ch0_active
  {
    byte ch=0;
    arrayControlData[ch][5] = mafFiltering(ch, arrayControlData[ch][0], arrayMafData);
    #ifdef ch0_analogLinear
      arrayChannelData[ch] = analogLinear(ch, arrayControlData, arrayServoData);
    #endif
  }
  #endif

  #ifdef ch1_active
  {
    byte ch=1;
    arrayControlData[ch][5] = mafFiltering(ch, arrayControlData[ch][0], arrayMafData);
    #ifdef ch1_analogLinear
      arrayChannelData[ch] = analogLinear(ch, arrayControlData, arrayServoData);
    #endif
  }
  #endif

  #ifdef ch2_active
  {
    byte ch=2;
    arrayControlData[ch][5] = mafFiltering(ch, arrayControlData[ch][0], arrayMafData);
    #ifdef ch2_analogLinear
      arrayChannelData[ch] = analogLinear(ch, arrayControlData, arrayServoData);
    #endif
  }
  #endif

  #ifdef ch3_active
  {
    byte ch=3;
    arrayControlData[ch][5] = mafFiltering(ch, arrayControlData[ch][0], arrayMafData);
    #ifdef ch3_analogLinear
      arrayChannelData[ch] = analogLinear(ch, arrayControlData, arrayServoData);
    #endif
  }
  #endif

  #ifdef ch4_active
  {
    byte ch=4;
    arrayControlData[ch][5] = mafFiltering(ch, arrayControlData[ch][0], arrayMafData);
    #ifdef ch4_analogLinear
      arrayChannelData[ch] = analogLinear(ch, arrayControlData, arrayServoData);
    #endif
  }
  #endif

  #ifdef ch5_active
  {
    byte ch=5;
    arrayControlData[ch][5] = mafFiltering(ch, arrayControlData[ch][0], arrayMafData);
    #ifdef ch5_analogLinear
      arrayChannelData[ch] = analogLinear(ch, arrayControlData, arrayServoData);
    #endif
  }
  #endif

  #ifdef ch6_active
  {
    byte ch=6;
    arrayControlData[ch][5] = mafFiltering(ch, arrayControlData[ch][0], arrayMafData);
    #ifdef ch6_analogLinear
      arrayChannelData[ch] = analogLinear(ch, arrayControlData, arrayServoData);
    #endif
  }
  #endif

  #ifdef ch7_active
  {
    byte ch=7;
    arrayControlData[ch][5] = mafFiltering(ch, arrayControlData[ch][0], arrayMafData);
    #ifdef ch7_analogLinear
      arrayChannelData[ch] = analogLinear(ch, arrayControlData, arrayServoData);
    #endif
  }
  #endif

  #ifdef ch8_active
  {
    byte ch=8;
    arrayControlData[ch][5] = mafFiltering(ch, arrayControlData[ch][0], arrayMafData);
    #ifdef ch8_analogLinear
      arrayChannelData[ch] = analogLinear(ch, arrayControlData, arrayServoData);
    #endif
  }
  #endif

  #ifdef ch9_active
  {
    byte ch=9;
    arrayControlData[ch][5] = mafFiltering(ch, arrayControlData[ch][0], arrayMafData);
    #ifdef ch9_analogLinear
      arrayChannelData[ch] = analogLinear(ch, arrayControlData, arrayServoData);
    #endif
  }
  #endif

  #ifdef ch10_active
  {
    byte ch=10;
    arrayControlData[ch][5] = mafFiltering(ch, arrayControlData[ch][0], arrayMafData);
    #ifdef ch10_analogLinear
      arrayChannelData[ch] = analogLinear(ch, arrayControlData, arrayServoData);
    #endif
  }
  #endif

  #ifdef ch11_active
  {
    byte ch=11;
    arrayControlData[ch][5] = mafFiltering(ch, arrayControlData[ch][0], arrayMafData);
    #ifdef ch11_analogLinear
      arrayChannelData[ch] = analogLinear(ch, arrayControlData, arrayServoData);
    #endif
  }
  #endif

  #ifdef ch12_active
  {
    byte ch=12;
    arrayControlData[ch][5] = mafFiltering(ch, arrayControlData[ch][0], arrayMafData);
    #ifdef ch12_analogLinear
      arrayChannelData[ch] = analogLinear(ch, arrayControlData, arrayServoData);
    #endif
  }
  #endif

  #ifdef ch13_active
  {
    byte ch=13;
    arrayControlData[ch][5] = mafFiltering(ch, arrayControlData[ch][0], arrayMafData);
    #ifdef ch13_analogLinear
      arrayChannelData[ch] = analogLinear(ch, arrayControlData, arrayServoData);
    #endif
  }
  #endif



  #ifdef ch14_active
  {
    byte ch=14;
    #ifdef ch14_digital2Way
      arrayChannelData[ch] = digital2Way(ch, pin_ch14);
    #endif
    #ifdef ch14_digital3Way
      arrayChannelData[ch] = digital3Way(ch, pin_ch14);
    #endif
  }
  #endif

  #ifdef ch15_active
  {
    byte ch=15;
    #ifdef ch15_digital2Way
      arrayChannelData[ch] = digital2Way(ch, pin_ch15);
    #endif
  }
  #endif

  #ifdef ch16_active
  {
    byte ch=16;
    #ifdef ch16_digital2Way
      arrayChannelData[ch] = digital2Way(ch, pin_ch16);
    #endif
    #ifdef ch16_digital3Way
      arrayChannelData[ch] = digital3Way(ch, pin_ch16);
    #endif
  }
  #endif

  #ifdef ch17_active
  {
    byte ch=17;
    #ifdef ch17_digital2Way
      arrayChannelData[ch] = digital2Way(ch, pin_ch17);
    #endif
  }
  #endif

  #ifdef ch18_active
  {
    byte ch=18;
    #ifdef ch18_digital2Way
      arrayChannelData[ch] = digital2Way(ch, pin_ch18);
    #endif
    #ifdef ch18_digital3Way
      arrayChannelData[ch] = digital3Way(ch, pin_ch18);
    #endif
  }
  #endif

  #ifdef ch19_active
  {
    byte ch=19;
    #ifdef ch19_digital2Way
      arrayChannelData[ch] = digital2Way(ch, pin_ch19);
    #endif
  }
  #endif

  #ifdef ch20_active
  {
    byte ch=20;
    #ifdef ch20_digital2Way
      arrayChannelData[ch] = digital2Way(ch, pin_ch20);
    #endif
    #ifdef ch20_digital3Way
      arrayChannelData[ch] = digital3Way(ch, pin_ch20);
    #endif
  }
  #endif

  #ifdef ch21_active
  {
    byte ch=21;
    #ifdef ch21_digital2Way
      arrayChannelData[ch] = digital2Way(ch, pin_ch21);
    #endif
  }
  #endif

  #ifdef ch22_active
  {
    byte ch=22;
    #ifdef ch22_digital2Way
      arrayChannelData[ch] = digital2Way(ch, pin_ch22);
    #endif
  }
  #endif

  #ifdef ch23_active
  {
    byte ch=23;
    #ifdef ch23_digital2Way
      arrayChannelData[ch] = digital2Way(ch, pin_ch23);
    #endif
  }
  #endif

  #ifdef ch24_active
  {
    byte ch=24;
    #ifdef ch24_digital2Way
      arrayChannelData[ch] = digital2Way(ch, pin_ch24);
    #endif
  }
  #endif

  #ifdef ch25_active
  {
    byte ch=25;
    #ifdef ch25_digital2Way
      arrayChannelData[ch] = digital2Way(ch, pin_ch25);
    #endif
  }
  #endif

  #ifdef ch26_active
  {
    byte ch=26;
    #ifdef ch26_digital2Way
      arrayChannelData[ch] = digital2Way(ch, pin_ch26);
    #endif
  }
  #endif

  #ifdef ch27_active
  {
    byte ch=27;
    #ifdef ch27_digital2Way
      arrayChannelData[ch] = digital2Way(ch, pin_ch27);
    #endif
  }
  #endif

  #ifdef ch28_active
  {
    byte ch=28;
    #ifdef ch28_digital2Way
      arrayChannelData[ch] = digital2Way(ch, pin_ch28);
    #endif
  }
  #endif

  #ifdef ch29_active
  {
    byte ch=29;
    #ifdef ch29_digital2Way
      arrayChannelData[ch] = digital2Way(ch, pin_ch29);
    #endif
  }
  #endif
}