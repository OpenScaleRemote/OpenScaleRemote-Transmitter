#include "IO_PCF8575.h"

void IO_PCF8575::pcf8575setup(){
  // Set pinMode to OUTPUT
  for(int i=0;i<16;i++) {
    pcf8575.pinMode(i, INPUT);
  }
  pcf8575.begin();
}

void IO_PCF8575::readpcf8575(int arrayControlData[30][6]) {
  PCF8575::DigitalInput di = PCF8575.digitalReadAll();
  #ifdef ch14_active
    arrayControlData[14][0] = di.p0;
  #endif

  #ifdef ch15_active
    arrayControlData[15][0] = di.p1;
  #endif

  #ifdef ch16_active
    arrayControlData[16][0] = di.p2;
  #endif

  #ifdef ch17_active
    arrayControlData[17][0] = di.p3;
  #endif

  #ifdef ch18_active
    arrayControlData[18][0] = di.p4;
  #endif

  #ifdef ch19_active
    arrayControlData[19][0] = di.p5;
  #endif

  #ifdef ch20_active
    arrayControlData[20][0] = di.p6;
  #endif

  #ifdef ch21_active
    arrayControlData[21][0] = di.p7;
  #endif

  #ifdef ch22_active
    arrayControlData[22][0] = di.p8;
  #endif

  #ifdef ch23_active
    arrayControlData[23][0] = di.p9;
  #endif

  #ifdef ch24_active
    arrayControlData[24][0] = di.p10;
  #endif

  #ifdef ch25_active
    arrayControlData[25][0] = di.p11;
  #endif

  #ifdef ch26_active
    arrayControlData[26][0] = di.p12;
  #endif

  #ifdef ch27_active
    arrayControlData[27][0] = di.p13;
  #endif

  #ifdef ch28_active
    arrayControlData[28][0] = di.p14;
  #endif

  #ifdef ch29_active
    arrayControlData[29][0] = di.p15;
  #endif
}