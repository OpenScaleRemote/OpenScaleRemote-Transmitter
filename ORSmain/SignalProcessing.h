#include "Arduino.h"
class SignalProcessing {
  public:
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
    //servoLowerLimit, servoUpperLimit, servoZeroPoint, servoInverse
    int channelData[16][4] = {{0,180,90,0},
                              {60,120,90,1},
                              {35,130,70,1},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0}};
  public:
  int analogLinear(int inputChannel);
  int digital2Way(int referenceChannel, int inputChannel);
  int digital3Way(int referenceChannel, int inputChannel);
};
