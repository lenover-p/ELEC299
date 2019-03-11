#include <EEPROM.h>
#define LBUMP 8
#define RBUMP 9
#define LSPEED 5
#define LDIR 4
#define RSPEED 6
#define RDIR 7
#define LENC 11
#define RENC 10


byte left_speed, right_speed;

void setup() {
  // put your setup code here, to run once:
  pinMode(LBUMP, INPUT);
  pinMode(RBUMP, INPUT);
  pinMode(LSPEED, OUTPUT);
  pinMode(LDIR, OUTPUT);
  pinMode(RSPEED, OUTPUT);
  pinMode(RDIR, OUTPUT);
  pinMode(RENC,INPUT);
  pinMode(LENC, INPUT);
  digitalWrite(LDIR, HIGH);
  digitalWrite(RDIR, HIGH);
  analogWrite(LSPEED, 0);
  analogWrite(RSPEED, 0);
  Serial.begin(9600);
  left_speed = EEPROM.read(0);
  right_speed = EEPROM.read(1);
  WaitButton();
}

void loop() {
  // put your main code here, to run repeatedly:
  Forward();
  AdjustSpeeds();
}

void Forward() {
  Serial.print("forward");
  digitalWrite(LDIR, HIGH);
  digitalWrite(RDIR, HIGH);
  analogWrite(LSPEED, left_speed);
  analogWrite(RSPEED, right_speed);
  delay(300);
}

void WaitButton() {
  while(1){
    if (digitalRead(LBUMP) == LOW || digitalRead(RBUMP) == LOW){
      return;
    }
  }
}

void AdjustSpeeds() {
  if (digitalRead(LBUMP) == LOW || digitalRead(RBUMP) == LOW) {
    delay(500);
    if (digitalRead(LBUMP) == LOW && digitalRead(RBUMP) == HIGH) {
      right_speed += 5;
      left_speed -= 5;
    }
    else if (digitalRead(LBUMP) == HIGH && digitalRead(RBUMP) == LOW) {
      right_speed -= 5;
      left_speed += 5;
    }
    if (digitalRead(LBUMP) == LOW && digitalRead(RBUMP) == LOW) {
      EEPROM.write(0, left_speed);
      EEPROM.write(1, right_speed);

      right_speed = left_speed = 0;
      delay(100);
    }
  }
}
