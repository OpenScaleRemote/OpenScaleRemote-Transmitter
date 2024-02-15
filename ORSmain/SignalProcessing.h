#include "Arduino.h"
#include "config.h"

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
    int servoData[30][4] = {{0,180,90,0},      //0
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},     //10
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},     //20
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0},
                              {0,180,90,0}};

    struct channelData {
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
      byte sD16=0;
      byte sD17=0;
      byte sD18=0;
      byte sD19=0;
      byte sD20=0;
      byte sD21=0;
      byte sD22=0;
      byte sD23=0;
      byte sD24=0;
      byte sD25=0;
      byte sD26=0;
      byte sD27=0;
      byte sD28=0;
      byte sD29=0;
    };
    channelData channelData;

    //array for moving average filter
    int mafData[14][windowSize+2] = {};  // index (0), sum (1), readings[windowSize] (3-windowSize-1)

  public:
    void setupSP();
    void processData();
    int mafFiltering(int a, int b);
    int analogLinear(int inputChannel);
    int digital2Way(int referenceChannel, int inputChannel);
    int digital3Way(int referenceChannel, int inputChannel);
};
