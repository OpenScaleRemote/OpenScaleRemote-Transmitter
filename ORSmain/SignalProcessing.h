# include "Arduino.h"
# include "config.h"

class SignalProcessing {
  public:
    //array for control data
    //channelInputData, channelLowerLimit, channelUpperLimit, channelZeroPoint, channelDeadZone, channelFiltered
    int controlData[30][6] = {{0,0,1023,511,0,0},
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
    
    //array for servo data
    //servoLowerLimit, servoUpperLimit, servoZeroPoint, servoInverse
    int servoData[30][4] = {{0,180,90,0},
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
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0}};

    //array for moving average filter
    int mafData[14][windowSize+2] = {};  // index (0), sum (1), readings[windowSize] (3-windowSize-1)

  public:
    void setupSP();
    int mafFiltering(int a, int b);
    int analogLinear(int inputChannel);
    int digital2Way(int referenceChannel, int inputChannel);
    int digital3Way(int referenceChannel, int inputChannel);
};
