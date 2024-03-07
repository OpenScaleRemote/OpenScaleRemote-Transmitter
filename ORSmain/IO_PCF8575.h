#include "Arduino.h"
#include "config.h"
#include "PCF8575.h"

class IO_PCF8575 {
  public:
    PCF8575 pcf8575(0x20);
  public:
  void pcf8575Setup();
  void readpcf8575(int arrayControlData[30][6]);

}