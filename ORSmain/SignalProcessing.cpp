# include "SignalProcessing.h"
  
int SignalProcessing::analogLinear(int inputChannel) {
  switch(channelData[inputChannel][3]) {
    case 0:
      if(controlData[inputChannel][5] < (controlData[inputChannel][3]-controlData[inputChannel][4])) {
        return map(controlData[inputChannel][5], controlData[inputChannel][1], (controlData[inputChannel][3]-controlData[inputChannel][4]), channelData[inputChannel][0], (channelData[inputChannel][2]-1));
      }else if(controlData[inputChannel][5] > (controlData[inputChannel][3]+controlData[inputChannel][4])) {
        return map(controlData[inputChannel][5], (controlData[inputChannel][3]+controlData[inputChannel][4]), controlData[inputChannel][2], (channelData[inputChannel][2]-1), channelData[inputChannel][1]);
      }else {
        return channelData[inputChannel][2];
      }
      break;
    case 1:
      if(controlData[inputChannel][5] < (controlData[inputChannel][3]-controlData[inputChannel][4])) {
        return map(controlData[inputChannel][5], controlData[inputChannel][1], (controlData[inputChannel][3]-controlData[inputChannel][4]), channelData[inputChannel][1], (channelData[inputChannel][2]+1));
      }else if(controlData[inputChannel][5] > (controlData[inputChannel][3]+controlData[inputChannel][4])) {
        return map(controlData[inputChannel][5], (controlData[inputChannel][3]+controlData[inputChannel][4]), controlData[inputChannel][2], (channelData[inputChannel][2]-1), channelData[inputChannel][0]);
      }else {
        return channelData[inputChannel][2];
      }
      break;
    default:
      Serial.print("Falscher Wert Servoinvertierung Kanal: ");
      Serial.println(inputChannel);
  }
}

int SignalProcessing::digital2Way(int referenceChannel, int inputChannel) {
  switch(channelData[inputChannel][3]) {
    case 0:
      if(digitalRead(inputChannel) == HIGH) {
        return channelData[referenceChannel][1];
      }else {
        return channelData[referenceChannel][0];
      }
      break;
    case 1:
      if(digitalRead(inputChannel) == HIGH) {
        return channelData[referenceChannel][0];
      }else {
        return channelData[referenceChannel][1];
      }
      break;
    default:
      Serial.print("Falscher Wert Servoinvertierung Kanal: ");
      Serial.println(referenceChannel);
  }
}

int SignalProcessing::digital3Way(int referenceChannel, int inputChannel) {
  switch(channelData[inputChannel][3]) {
    case 0:
      if(digitalRead(inputChannel) == HIGH && digitalRead(inputChannel+1) == LOW) {
        return channelData[referenceChannel][1];
      }else if(digitalRead(inputChannel) == LOW && digitalRead(inputChannel+1) == HIGH) {
        return channelData[referenceChannel][0];
      }else {
        return channelData[referenceChannel][2];
      }
      break;
    case 1:
      if(digitalRead(inputChannel) == HIGH && digitalRead(inputChannel+1) == LOW) {
        return channelData[referenceChannel][0];
      }else if(digitalRead(inputChannel) == LOW && digitalRead(inputChannel+1) == HIGH) {
        return channelData[referenceChannel][1];
      }else {
        return channelData[referenceChannel][2];
      }
      break;
    default:
      Serial.print("Falscher Wert Servoinvertierung Kanal: ");
      Serial.println(referenceChannel);
  }
}
