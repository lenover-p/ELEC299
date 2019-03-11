#define RSPEED 6
#define RDIR 7
#define LSPEED  5
#define LDIR 4
#define BUTTONPIN 1

void setup() {
  // put your setup code here, to run once:
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
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RDIR, HIGH);
  digitalWrite(LDIR, LOW);
  //

  analogWrite(RSPEED, 100);
  analogWrite(LSPEED, 100);

  delay(3000);
  digitalWrite(LDIR, HIGH);
  digitalWrite(RDIR, LOW);

  delay(3000);
  digitalWrite(RDIR, HIGH);
  digitalWrite(LDIR, LOW);
  
}
