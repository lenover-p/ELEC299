#define LINEL A1
#define LINEM A2
#define LINER A0
#define RSPEED 6
#define RDIR 7
#define LSPEED  5
#define LDIR 4
#define BUTTONPIN 1

void setup() {
  // put your setup code here, to run once:
  pinMode(LINER, INPUT);
  pinMode(LINEM, INPUT);
  pinMode(LINEL, INPUT);

  pinMode(RSPEED, OUTPUT);
  pinMode(RDIR, OUTPUT);
  pinMode(LSPEED, OUTPUT);
  pinMode(LDIR, OUTPUT);

  analogWrite(RSPEED, 0);
  analogWrite(LSPEED, 0);

  while(1) {
    if (digitalRead(BUTTONPIN) == LOW) {
      break;
    }
  }
  while(1) {
    if (digitalRead(BUTTONPIN) == HIGH) {
      delay(10);
      if (digitalRead(BUTTONPIN) == HIGH) {
        break;
      }
    }
  }
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RDIR, HIGH);
  digitalWrite(LDIR, HIGH);
  if (analogRead(LINEM) >= 1000) {
    analogWrite(RSPEED, 100);
    analogWrite(LSPEED, 100);
    Serial.print("going straight\n");
  }
  else if (analogRead(LINER) >= 1000) {
    Serial.print("turning right\n");
    while(1) {
      analogWrite(RSPEED, 0);
      analogWrite(LSPEED, 100);
      if (analogRead(LINEM) >= 1000){
        analogWrite(RSPEED, 100);
        analogWrite(LSPEED, 100);
        break;
      }
    }    
  }
  else if (analogRead(LINEL) >= 1000) {
    Serial.print("turning left\n");
    while(1) {
      analogWrite(RSPEED, 100);
      analogWrite(LSPEED, 0);
      if (analogRead(LINEM) >= 1000){
        analogWrite(RSPEED, 100);
        analogWrite(LSPEED, 100);
        break;
      }
    }
  }

}
