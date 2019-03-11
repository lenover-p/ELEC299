#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Left Speed: ");
  Serial.println(EEPROM.read(0));
  Serial.print("Right Speed: ");
  Serial.println(EEPROM.read(1));
}

void loop() {
  // put your main code here, to run repeatedly:
  return;
}
