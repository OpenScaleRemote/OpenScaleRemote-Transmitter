#include "SignalProcessing.h"

int SignalProcessing::mafFiltering(int b, int a) {
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



int SignalProcessing::analogLinear(int inputChannel) {
  switch(servoData[inputChannel][3]) {
    case 0:
      if(controlData[inputChannel][5] < (controlData[inputChannel][3]-controlData[inputChannel][4])) {
        return map(controlData[inputChannel][5], controlData[inputChannel][1], (controlData[inputChannel][3]-controlData[inputChannel][4]), servoData[inputChannel][0], (servoData[inputChannel][2]-1));
      }else if(controlData[inputChannel][5] > (controlData[inputChannel][3]+controlData[inputChannel][4])) {
        return map(controlData[inputChannel][5], (controlData[inputChannel][3]+controlData[inputChannel][4]), controlData[inputChannel][2], (servoData[inputChannel][2]-1), servoData[inputChannel][1]);
      }else {
        return servoData[inputChannel][2];
      }
      break;
    case 1:
      if(controlData[inputChannel][5] < (controlData[inputChannel][3]-controlData[inputChannel][4])) {
        return map(controlData[inputChannel][5], controlData[inputChannel][1], (controlData[inputChannel][3]-controlData[inputChannel][4]), servoData[inputChannel][1], (servoData[inputChannel][2]+1));
      }else if(controlData[inputChannel][5] > (controlData[inputChannel][3]+controlData[inputChannel][4])) {
        return map(controlData[inputChannel][5], (controlData[inputChannel][3]+controlData[inputChannel][4]), controlData[inputChannel][2], (servoData[inputChannel][2]-1), servoData[inputChannel][0]);
      }else {
        return servoData[inputChannel][2];
      }
      break;
    default:
      Serial.print("Falscher Wert Servoinvertierung Kanal: ");
      Serial.println(inputChannel);
      return 90;
  }
}



int SignalProcessing::digital2Way(int inputChannel, int inputChannelPin) {
  switch(servoData[inputChannel][3]) {
    case 0:
      if(digitalRead(inputChannelPin) == 0) {
        return servoData[inputChannel][1];
      }else {
        return servoData[inputChannel][0];
      }
      break;
    case 1:
      if(digitalRead(inputChannelPin) == 0) {
        return servoData[inputChannel][0];
      }else {
        return servoData[inputChannel][1];
      }
      break;
    default:
      Serial.print("Falscher Wert Servoinvertierung Kanal: ");
      Serial.println(inputChannel);
      return 90;
  }
}



int SignalProcessing::digital3Way(int inputChannel, int inputChannelPin) {
  switch(servoData[inputChannel][3]) {
    case 0:
      if(digitalRead(inputChannelPin) == HIGH && digitalRead(inputChannelPin+1) == LOW) {
        return servoData[inputChannel][1];
      }else if(digitalRead(inputChannelPin) == LOW && digitalRead(inputChannelPin+1) == HIGH) {
        return servoData[inputChannel][0];
      }else {
        return servoData[inputChannel][2];
      }
      break;
    case 1:
      if(digitalRead(inputChannelPin) == HIGH && digitalRead(inputChannelPin+1) == LOW) {
        return servoData[inputChannel][0];
      }else if(digitalRead(inputChannelPin) == LOW && digitalRead(inputChannelPin+1) == HIGH) {
        return servoData[inputChannel][1];
      }else {
        return servoData[inputChannel][2];
      }
      break;
    default:
      Serial.print("Falscher Wert Servoinvertierung Kanal: ");
      Serial.println(inputChannel);
      return 90;
  }
}



void SignalProcessing::processData() {
  #ifdef ch0_active
    controlData[0][0] = analogRead(pin_ch0);
    controlData[0][5] = mafFiltering(controlData[0][0], 0);
    #ifdef ch0_analogLinear
      channelData.sD0 = analogLinear(0);
    #endif
  #endif

  #ifdef ch1_active
    controlData[1][0] = analogRead(pin_ch1);
    controlData[1][5] = mafFiltering(controlData[1][0], 1);
    #ifdef ch1_analogLinear
      channelData.sD1 = analogLinear(1);
    #endif
  #endif

  #ifdef ch2_active
    controlData[2][0] = analogRead(pin_ch2);
    controlData[2][5] = mafFiltering(controlData[2][0], 2);
    #ifdef ch2_analogLinear
      channelData.sD2 = analogLinear(2);
    #endif
  #endif

  #ifdef ch3_active
    controlData[3][0] = analogRead(pin_ch3);
    controlData[3][5] = mafFiltering(controlData[3][0], 3);
    #ifdef ch3_analogLinear
      channelData.sD3 = analogLinear(3);
    #endif
  #endif

  #ifdef ch4_active
    controlData[4][0] = analogRead(pin_ch4);
    controlData[4][5] = mafFiltering(controlData[4][0], 4);
    #ifdef ch4_analogLinear
      channelData.sD4 = analogLinear(4);
    #endif
  #endif

  #ifdef ch5_active
    controlData[5][0] = analogRead(pin_ch5);
    controlData[5][5] = mafFiltering(controlData[5][0], 5);
    #ifdef ch5_analogLinear
      channelData.sD5 = analogLinear(5);
    #endif
  #endif

  #ifdef ch6_active
    controlData[6][0] = analogRead(pin_ch6);
    controlData[6][5] = mafFiltering(controlData[6][0], 6);
    #ifdef ch6_analogLinear
      channelData.sD6 = analogLinear(6);
    #endif
  #endif

  #ifdef ch7_active
    controlData[7][0] = analogRead(pin_ch7);
    controlData[7][5] = mafFiltering(controlData[7][0], 7);
    #ifdef ch7_analogLinear
      channelData.sD7 = analogLinear(7);
    #endif
  #endif

  #ifdef ch8_active
    controlData[8][0] = analogRead(pin_ch8);
    controlData[8][5] = mafFiltering(controlData[8][0], 8);
    #ifdef ch8_analogLinear
      channelData.sD8 = analogLinear(8);
    #endif
  #endif

  #ifdef ch9_active
    controlData[9][0] = analogRead(pin_ch9);
    controlData[9][5] = mafFiltering(controlData[9][0], 9);
    #ifdef ch9_analogLinear
      channelData.sD9 = analogLinear(9);
    #endif
  #endif

  #ifdef ch10_active
    controlData1[0][0] = analogRead(pin_ch10);
    controlData[10][5] = mafFiltering(controlData[10][0], 10);
    #ifdef ch11_analogLinear
      channelData.sD10 = analogLinear(10);
    #endif
  #endif

  #ifdef ch11_active
    controlData[11][0] = analogRead(pin_ch11);
    controlData[11][5] = mafFiltering(controlData[11][0], 11);
    #ifdef ch11_analogLinear
      channelData.sD11 = analogLinear(11);
    #endif
  #endif

  #ifdef ch12_active
    controlData[12][0] = analogRead(pin_ch12);
    controlData[12][5] = mafFiltering(controlData[12][0], 12);
    #ifdef ch12_analogLinear
      channelData.sD12 = analogLinear(12);
    #endif
  #endif

  #ifdef ch13_active
    controlData[13][0] = analogRead(pin_ch13);
    controlData[13][5] = mafFiltering(controlData[13][0], 13);
    #ifdef ch13_analogLinear
      channelData.sD13 = analogLinear(13);
    #endif
  #endif

  #ifdef ch14_active
    #ifdef ch14_digital2Way
      channelData.sD14 = digital2Way(14, pin_ch14);
    #endif
    #ifdef ch14_digital3Way
      channelData.sD14 = digital3Way(14, pin_ch14);
    #endif
  #endif

  #ifdef ch15_active
    #ifdef ch15_digital2Way
      channelData.sD15 = digital2Way(15, pin_ch15);
    #endif
  #endif

  #ifdef ch16_active
    #ifdef ch16_digital2Way
      channelData.sD16 = digital2Way(16, pin_ch16);
    #endif
    #ifdef ch16_digital3Way
      channelData.sD16 = digital3Way(16, pin_ch16);
    #endif
  #endif

  #ifdef ch17_active
    #ifdef ch17_digital2Way
      channelData.sD17 = digital2Way(17, pin_ch17);
    #endif
  #endif

  #ifdef ch18_active
    #ifdef ch18_digital2Way
      channelData.sD18 = digital2Way(18, pin_ch18);
    #endif
    #ifdef ch18_digital3Way
      channelData.sD18 = digital3Way(18, pin_ch18);
    #endif
  #endif

  #ifdef ch19_active
    #ifdef ch19_digital2Way
      channelData.sD19 = digital2Way(19, pin_ch19);
    #endif
  #endif

  #ifdef ch20_active
    #ifdef ch20_digital2Way
      channelData.sD20 = digital2Way(20, pin_ch20);
    #endif
    #ifdef ch20_digital3Way
      channelData.sD20 = digital3Way(20, pin_ch20);
    #endif
  #endif

  #ifdef ch21_active
    #ifdef ch21_digital2Way
      channelData.sD21 = digital2Way(21, pin_ch21);
    #endif
  #endif

  #ifdef ch22_active
    #ifdef ch22_digital2Way
      channelData.sD22 = digital2Way(22, pin_ch22);
    #endif
  #endif

  #ifdef ch23_active
    #ifdef ch23_digital2Way
      channelData.sD23 = digital2Way(23, pin_ch23);
    #endif
  #endif

  #ifdef ch24_active
    #ifdef ch24_digital2Way
      channelData.sD24 = digital2Way(24, pin_ch24);
    #endif
  #endif

  #ifdef ch25_active
    #ifdef ch25_digital2Way
      channelData.sD25 = digital2Way(25, pin_ch25);
    #endif
  #endif

  #ifdef ch26_active
    #ifdef ch26_digital2Way
      channelData.sD26 = digital2Way(26, pin_ch26);
    #endif
  #endif

  #ifdef ch27_active
    #ifdef ch27_digital2Way
      channelData.sD27 = digital2Way(27, pin_ch27);
    #endif
  #endif

  #ifdef ch28_active
    #ifdef ch28_digital2Way
      channelData.sD28 = digital2Way(28, pin_ch28);
    #endif
  #endif

  #ifdef ch29_active
    #ifdef ch29_digital2Way
      channelData.sD29 = digital2Way(29, pin_ch29);
    #endif
  #endif
}