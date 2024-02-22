#include "WirelessCommunication.h"

void WirelessCommunication::loraSetup() {
  Serial.println("LoRa Sender");
  Serial.println("Starting LoRa");
  LoRa.setPins(rfm95w_cs, rfm95w_reset, rfm95w_dio0);
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  else {
    Serial.println("Starting LoRa successfull!");
  }
  delay(2000);
}



void WirelessCommunication::writeFast1(byte arrayChannelData[30]) {
  #ifdef ch0_fast1

    LoRa.write(arrayChannelData[0]);
  #endif

  #ifdef ch1_fast1
    LoRa.write(arrayChannelData[1]);
  #endif

  #ifdef ch2_fast1
    LoRa.write(arrayChannelData[2]);
  #endif

  #ifdef ch3_fast1
    LoRa.write(arrayChannelData[3]);
  #endif

  #ifdef ch4_fast1
    LoRa.write(arrayChannelData[4]);
  #endif

  #ifdef ch5_fast1
    LoRa.write(arrayChannelData[5]);
  #endif

  #ifdef ch6_fast1
    LoRa.write(arrayChannelData[6]);
  #endif

  #ifdef ch7_fast1
    LoRa.write(arrayChannelData[7]);
  #endif

  #ifdef ch8_fast1
    LoRa.write(arrayChannelData[8]);
  #endif

  #ifdef ch9_fast1
    LoRa.write(arrayChannelData[9]);
  #endif

  #ifdef ch10_fast1
    LoRa.write(arrayChannelData[10]);
  #endif

  #ifdef ch11_fast1
    LoRa.write(arrayChannelData[11]);
  #endif

  #ifdef ch12_fast1
    LoRa.write(arrayChannelData[12]);
  #endif

  #ifdef ch13_fast1
    LoRa.write(arrayChannelData[13]);
  #endif

  #ifdef ch14_fast1
    LoRa.write(arrayChannelData[14]);
  #endif

  #ifdef ch15_fast1
    LoRa.write(arrayChannelData[15]);
  #endif

  #ifdef ch16_fast1
    LoRa.write(arrayChannelData[16]);
  #endif

  #ifdef ch17_fast1
    LoRa.write(arrayChannelData[17]);
  #endif

  #ifdef ch18_fast1
    LoRa.write(arrayChannelData[18]);
  #endif

  #ifdef ch19_fast1
    LoRa.write(arrayChannelData[19]);
  #endif

  #ifdef ch20_fast1
    LoRa.write(arrayChannelData[20]);
  #endif

  #ifdef ch21_fast1
    LoRa.write(arrayChannelData[21]);
  #endif

  #ifdef ch22_fast1
    LoRa.write(arrayChannelData[22]);
  #endif

  #ifdef ch23_fast1
    LoRa.write(arrayChannelData[23]);
  #endif

  #ifdef ch24_fast1
    LoRa.write(arrayChannelData[24]);
  #endif

  #ifdef ch25_fast1
    LoRa.write(arrayChannelData[25]);
  #endif

  #ifdef ch26_fast1
    LoRa.write(arrayChannelData[26]);
  #endif

  #ifdef ch27_fast1
    LoRa.write(arrayChannelData[27]);
  #endif

  #ifdef ch28_fast1
    LoRa.write(arrayChannelData[28]);
  #endif

  #ifdef ch29_fast1
    LoRa.write(arrayChannelData[29]);
  #endif
}



void WirelessCommunication::writeFast2(byte arrayChannelData[30]) {
  #ifdef ch0_fast2
    LoRa.write(arrayChannelData[0]);
  #endif

  #ifdef ch1_fast2
    LoRa.write(arrayChannelData[1]);
  #endif

  #ifdef ch2_fast2
    LoRa.write(arrayChannelData[2]);
  #endif

  #ifdef ch3_fast2
    LoRa.write(arrayChannelData[3]);
  #endif

  #ifdef ch4_fast2
    LoRa.write(arrayChannelData[4]);
  #endif

  #ifdef ch5_fast2
    LoRa.write(arrayChannelData[5]);
  #endif

  #ifdef ch6_fast2
    LoRa.write(arrayChannelData[6]);
  #endif

  #ifdef ch7_fast2
    LoRa.write(arrayChannelData[7]);
  #endif

  #ifdef ch8_fast2
    LoRa.write(arrayChannelData[8]);
  #endif

  #ifdef ch9_fast2
    LoRa.write(arrayChannelData[9]);
  #endif

  #ifdef ch10_fast2
    LoRa.write(arrayChannelData[10]);
  #endif

  #ifdef ch11_fast2
    LoRa.write(arrayChannelData[11]);
  #endif

  #ifdef ch12_fast2
    LoRa.write(arrayChannelData[12]);
  #endif

  #ifdef ch13_fast2
    LoRa.write(arrayChannelData[13]);
  #endif

  #ifdef ch14_fast2
    LoRa.write(arrayChannelData[14]);
  #endif

  #ifdef ch15_fast2
    LoRa.write(arrayChannelData[15]);
  #endif

  #ifdef ch16_fast2
    LoRa.write(arrayChannelData[16]);
  #endif

  #ifdef ch17_fast2
    LoRa.write(arrayChannelData[17]);
  #endif

  #ifdef ch18_fast2
    LoRa.write(arrayChannelData[18]);
  #endif

  #ifdef ch19_fast2
    LoRa.write(arrayChannelData[19]);
  #endif

  #ifdef ch20_fast2
    LoRa.write(arrayChannelData[20]);
  #endif

  #ifdef ch21_fast2
    LoRa.write(arrayChannelData[21]);
  #endif

  #ifdef ch22_fast2
    LoRa.write(arrayChannelData[22]);
  #endif

  #ifdef ch23_fast2
    LoRa.write(arrayChannelData[23]);
  #endif

  #ifdef ch24_fast2
    LoRa.write(arrayChannelData[24]);
  #endif

  #ifdef ch25_fast2
    LoRa.write(arrayChannelData[25]);
  #endif

  #ifdef ch26_fast2
    LoRa.write(arrayChannelData[26]);
  #endif

  #ifdef ch27_fast2
    LoRa.write(arrayChannelData[27]);
  #endif

  #ifdef ch28_fast2
    LoRa.write(arrayChannelData[28]);
  #endif

  #ifdef ch29_fast2
    LoRa.write(arrayChannelData29]);
  #endif
}



void WirelessCommunication::writeSlow(byte arrayChannelData[30]) {
  #ifdef ch0_slow
    LoRa.write(arrayChannelData[0]);
  #endif

  #ifdef ch1_slow
    LoRa.write(arrayChannelData[1]);
  #endif

  #ifdef ch2_slow
    LoRa.write(arrayChannelData[2]);
  #endif

  #ifdef ch3_slow
    LoRa.write(arrayChannelData[3]);
  #endif

  #ifdef ch4_slow
    LoRa.write(arrayChannelData[4]);
  #endif

  #ifdef ch5_slow
    LoRa.write(arrayChannelData[5]);
  #endif

  #ifdef ch6_slow
    LoRa.write(arrayChannelData[6]);
  #endif

  #ifdef ch7_slow
    LoRa.write(arrayChannelData[7]);
  #endif

  #ifdef ch8_slow
    LoRa.write(arrayChannelData[8]);
  #endif

  #ifdef ch9_slow
    LoRa.write(arrayChannelData[9]);
  #endif

  #ifdef ch10_slow
    LoRa.write(arrayChannelData[10]);
  #endif

  #ifdef ch11_slow
    LoRa.write(arrayChannelData[11]);
  #endif

  #ifdef ch12_slow
    LoRa.write(arrayChannelData[12]);
  #endif

  #ifdef ch13_slow
    LoRa.write(arrayChannelData[13]);
  #endif

  #ifdef ch14_slow
    LoRa.write(arrayChannelData[14]);
  #endif

  #ifdef ch15_slow
    LoRa.write(arrayChannelData[15]);
  #endif

  #ifdef ch16_slow
    LoRa.write(arrayChannelData[16]);
  #endif

  #ifdef ch17_slow
    LoRa.write(arrayChannelData[17]);
  #endif

  #ifdef ch18_slow
    LoRa.write(arrayChannelData[18]);
  #endif

  #ifdef ch19_slow
    LoRa.write(arrayChannelData[19]);
  #endif

  #ifdef ch20_slow
    LoRa.write(arrayChannelData[20]);
  #endif

  #ifdef ch21_slow
    LoRa.write(arrayChannelData[21]);
  #endif

  #ifdef ch22_slow
    LoRa.write(arrayChannelData[22]);
  #endif

  #ifdef ch23_slow
    LoRa.write(arrayChannelData[23]);
  #endif

  #ifdef ch24_slow
    LoRa.write(arrayChannelData[24]);
  #endif

  #ifdef ch25_slow
    LoRa.write(arrayChannelData[25]);
  #endif

  #ifdef ch26_slow
    LoRa.write(arrayChannelData[26]);
  #endif

  #ifdef ch27_slow
    LoRa.write(arrayChannelData[27]);
  #endif

  #ifdef ch28_slow
    LoRa.write(arrayChannelData[28]);
  #endif

  #ifdef ch29_slow
    LoRa.write(arrayChannelData[29]);
  #endif  
}



void WirelessCommunication::writeUltraSlow(byte arrayChannelData[30]) {
  #ifdef ch14_ultraSlow
    LoRa.write(arrayChannelData[14]);
  #endif

  #ifdef ch15_ultraSlow
    LoRa.write(arrayChannelData[15]);
  #endif

  #ifdef ch16_ultraSlow
    LoRa.write(arrayChannelData[16]);
  #endif

  #ifdef ch17_ultraSlow
    LoRa.write(arrayChannelData[17]);
  #endif

  #ifdef ch18_ultraSlow
    LoRa.write(arrayChannelData[18]);
  #endif

  #ifdef ch19_ultraSlow
    LoRa.write(arrayChannelData[19]);
  #endif

  #ifdef ch20_ultraSlow
    LoRa.write(arrayChannelData[20]);
  #endif

  #ifdef ch21_ultraSlow
    LoRa.write(arrayChannelData[21]);
  #endif

  #ifdef ch22_ultraSlow
    LoRa.write(arrayChannelData[22]);
  #endif

  #ifdef ch23_ultraSlow
    LoRa.write(arrayChannelData[23]);
  #endif

  #ifdef ch24_ultraSlow
    LoRa.write(arrayChannelData[24]);
  #endif

  #ifdef ch25_ultraSlow
    LoRa.write(arrayChannelData[25]);
  #endif

  #ifdef ch26_ultraSlow
    LoRa.write(arrayChannelData[26]);
  #endif

  #ifdef ch27_ultraSlow
    LoRa.write(arrayChannelData[27]);
  #endif

  #ifdef ch28_ultraSlow
    LoRa.write(arrayChannelData[28]);
  #endif

  #ifdef ch29_ultraSlow
    LoRa.write(arrayChannelData[29]);
  #endif    
}