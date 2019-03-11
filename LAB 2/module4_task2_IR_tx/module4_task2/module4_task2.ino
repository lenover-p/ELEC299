#include <QSerial.h>
QSerial myIRserial;

#define txpin 1
#define rxpin -1

void setup() {
  // put your setup code here, to run once:
  myIRserial.attach(rxpin, txpin);
}

void loop() {
  // put your main code here, to run repeatedly:
  myIRserial.transmit('3');
  delay(100);
  
}
