#define LBUMP 8
#define RBUMP 9
#define LSPEED 5
#define LDIR 4
#define RSPEED 6
#define RDIR 7
#define LENC 11
#define RENC 10



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
  WaitButton();
}

void loop() {
  // put your main code here, to run repeatedly:
  Forward();
  ReactBumpers();
}

void WaitButton() {
  while(1){
    if (digitalRead(LBUMP) == LOW || digitalRead(RBUMP) == LOW){
      return;
    }
  }
}

void Forward() {
  Serial.print("forward");
  digitalWrite(LDIR, HIGH);
  digitalWrite(RDIR, HIGH);
  analogWrite(LSPEED, 100);
  analogWrite(RSPEED, 100);
  delay(300);
}

void ReactBumpers() {
  if (digitalRead(LBUMP) == LOW && digitalRead(RBUMP) == LOW) {
    digitalWrite(LDIR, LOW);
    digitalWrite(RDIR, LOW);
    analogWrite(LSPEED, 100);
    analogWrite(RSPEED, 100);
    delay(1000);
    Rotate();
    Forward();
  }
  if (digitalRead(LBUMP) == LOW && digitalRead(RBUMP) == HIGH){
    digitalWrite(LDIR, LOW);
    digitalWrite(RDIR, LOW);
    analogWrite(LSPEED, 100);
    analogWrite(RSPEED, 100);
    delay(1000);
    TurnRight();
    Forward();
  }
  if (digitalRead(LBUMP) == HIGH && digitalRead(RBUMP) == LOW){
    digitalWrite(LDIR, LOW);
    digitalWrite(RDIR, LOW);
    analogWrite(LSPEED, 100);
    analogWrite(RSPEED, 100);
    delay(1000);
    TurnLeft();
    Forward();
  }
  delay(300);
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

void TurnRight() {
  int i = 0;
  int state = digitalRead(LENC);
  digitalWrite(LDIR, HIGH);
  digitalWrite(RDIR, LOW);
  while(i <= 4){
    if(digitalRead(LENC) == HIGH && state == 0) {
      i++;
      state = 1;
    }
    if (digitalRead(LENC) == LOW && state == 1) {
      i++;
      state = 0;
    }
  }
  analogWrite(RSPEED, 0);
  analogWrite(LSPEED, 0);
}

void TurnLeft() {
  int i = 0;
  int state = digitalRead(LENC);
  digitalWrite(LDIR, LOW);
  digitalWrite(RDIR, HIGH);
  while(i <= 4){
    if(digitalRead(LENC) == HIGH && state == 0) {
      i++;
      state = 1;
    }
    if (digitalRead(LENC) == LOW && state == 1) {
      i++;
      state = 0;
    }
  }
  analogWrite(RSPEED, 0);
  analogWrite(LSPEED, 0);
}
