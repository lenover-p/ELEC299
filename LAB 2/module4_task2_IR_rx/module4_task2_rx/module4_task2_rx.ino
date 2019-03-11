#include <QSerial.h>
QSerial myIRserial;

#define txpin -1
#define rxpin 12

void setup() {
  // put your setup code here, to run once:
  myIRserial.attach(rxpin, txpin);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = myIRserial.receive(200);
  if (val == 0){
    Serial.print("No start bit recieved\n");
  }
  else if (val == -1) {
    Serial.print("False start\n");
  }
  else if (val == -2) {
    Serial.print("Framing error\n");
  }
  else{
    Serial.print("Decimal Value: ");
    Serial.println(val);
    Serial.print("ASCII Character: ");
    Serial.println((char)val);
  }
}
