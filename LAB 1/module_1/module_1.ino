#define LEDPIN 8
//#define BUTTONPIN 4
#define POTPIN A3

void setup() {
  // put your setup code here, to run once:
  // pinMode(LEDPIN, OUTPUT);
  //pinMode(BUTTONPIN, INPUT);
  pinMode(POTPIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

int pot_level = analogRead(POTPIN);
Serial.print(pot_level);
Serial.print('\n');
digitalWrite(LEDPIN, HIGH);
        delay(pot_level);
        digitalWrite(LEDPIN, LOW);
        delay(pot_level);


/*if (digitalRead(BUTTONPIN) == LOW) {
  if (digitalRead(BUTTONPIN) == HIGH) {
    delay(5);
    if (digitalRead(BUTTONPIN) == HIGH) {
      while(1) {
        digitalWrite(LEDPIN, HIGH);
        delay(1000);
        digitalWrite(LEDPIN, LOW);
        delay(1000);
      }
    }
  }
}*/
}
