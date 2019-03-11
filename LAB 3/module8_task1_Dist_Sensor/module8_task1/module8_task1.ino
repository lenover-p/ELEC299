#include <EEPROM.h>
#define IR A2
#define LSPEED 5
#define LDIR 4
#define RSPEED 6
#define RDIR 7
#define LBUMP 8
#define RBUMP 9
#define LENC 11
#define RENC 10

byte left_speed, right_speed;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A2, INPUT);
  pinMode(LBUMP, INPUT);
  pinMode(RBUMP, INPUT);
  pinMode(LSPEED, OUTPUT);
  pinMode(LDIR, OUTPUT);
  pinMode(RSPEED, OUTPUT);
  pinMode(RDIR, OUTPUT);
  digitalWrite(LDIR, HIGH);
  digitalWrite(RDIR, HIGH);
  analogWrite(LSPEED, 0);
  analogWrite(RSPEED, 0);
  pinMode(RENC,INPUT);
  pinMode(LENC, INPUT);
  left_speed = EEPROM.read(0);
  right_speed = EEPROM.read(1);
  WaitButton();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A2));
  Forward();
  AdjustSpeeds();
  CheckDist();
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
      Serial.println("Button Pressed");
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

void Rotate() {
  int i = 0;
  int state = digitalRead(LENC);
  digitalWrite(LDIR, HIGH);
  digitalWrite(RDIR, LOW);
  analogWrite(LSPEED, 100);
  analogWrite(RSPEED, 100);
  while(i <= 16){
    if(digitalRead(LENC) == HIGH && state == 0) {
      i++;
      state = 1;
    }
    if (digitalRead(LENC) == LOW && state == 1) {
      i++;
      state = 0;
    }
    if (i >= 28){
      analogWrite(RSPEED, 90);
      analogWrite(LSPEED, 90);
    }
  }
  analogWrite(RSPEED, 0);
  analogWrite(LSPEED, 0);
}

void CheckDist() {
  if (analogRead(IR) >= 450) {
    analogWrite(LSPEED, 0);
    analogWrite(RSPEED, 0);
    delay(300);
    Rotate();
    delay(300);
  }
}
