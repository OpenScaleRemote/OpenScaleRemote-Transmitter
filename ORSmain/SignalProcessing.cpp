# include "SignalProcessing.h"

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

int SignalProcessing::digital2Way(int referenceChannel, int inputChannel) {
  switch(servoData[inputChannel][3]) {
    case 0:
      if(digitalRead(inputChannel) == HIGH) {
        return servoData[referenceChannel][1];
      }else {
        return servoData[referenceChannel][0];
      }
      break;
    case 1:
      if(digitalRead(inputChannel) == HIGH) {
        return servoData[referenceChannel][0];
      }else {
        return servoData[referenceChannel][1];
      }
      break;
    default:
      Serial.print("Falscher Wert Servoinvertierung Kanal: ");
      Serial.println(inputChannel);
      return 90;
  }
}

int SignalProcessing::digital3Way(int referenceChannel, int inputChannel) {
  switch(servoData[inputChannel][3]) {
    case 0:
      if(digitalRead(inputChannel) == HIGH && digitalRead(inputChannel+1) == LOW) {
        return servoData[referenceChannel][1];
      }else if(digitalRead(inputChannel) == LOW && digitalRead(inputChannel+1) == HIGH) {
        return servoData[referenceChannel][0];
      }else {
        return servoData[referenceChannel][2];
      }
      break;
    case 1:
      if(digitalRead(inputChannel) == HIGH && digitalRead(inputChannel+1) == LOW) {
        return servoData[referenceChannel][0];
      }else if(digitalRead(inputChannel) == LOW && digitalRead(inputChannel+1) == HIGH) {
        return servoData[referenceChannel][1];
      }else {
        return servoData[referenceChannel][2];
      }
      break;
    default:
      Serial.print("Falscher Wert Servoinvertierung Kanal: ");
      Serial.println(inputChannel);
      return 90;
  }
}
