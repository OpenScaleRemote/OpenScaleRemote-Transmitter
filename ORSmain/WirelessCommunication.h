#include "Arduino.h"
#include "config.h"
#include <LoRa.h>

class WirelessCommunication {
  public:
  bool fastSwitch = false;    //If fastSwitch is false, fast1 sending mode is active. If fastSwitch is true, fast2 sending mode is active.

  public:
  void loraSetup();
  void writeFast1(byte arrayChannelData[30]);
  void writeFast2(byte arrayChannelData[30]);
  void writeSlow(byte arrayChannelData[30]);
  void writeUltraSlow(byte arrayChannelData[30]);
};