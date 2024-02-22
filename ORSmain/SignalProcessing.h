#include "Arduino.h"
#include "config.h"

class SignalProcessing {
  public:

  public:
    void setupSP();
    void processData(int arrayMafData[14][2+windowSize],int arrayControlData[30][6], int arrayServoData[30][4], byte arrayChannelData[30]);
    int mafFiltering(int a, int b, int arrayMafData[14][2+windowSize]);
    int analogLinear(int inputChannel, int arraycontrolData[30][6], int arrayServoData[30][4]);
    int digital2Way(int referenceChannel, int inputChannel, int arrayServoData[30][4]);
    int digital3Way(int referenceChannel, int inputChannel, int arrayServoData[30][4]);
};
