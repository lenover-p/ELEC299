#include <Servo.h>
Servo grip_servo, pan_servo, tilt_servo;

#define LBUMP 2
#define IRRX 3
#define RDIR 4
#define RSPEED 5
#define LSPEED 6
#define LDIR 7
#define RBUMP 8
#define LENC 9
#define RENC 10
#define PAN 11
#define TILT 12
#define GRIP 13
#define FORCE A1
#define DIST A2
#define LINEM A3
#define LINEL A4
#define LINER A5


int rSpeed = 100;
int lSpeed = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(LBUMP, INPUT);
  pinMode(IRRX, INPUT);
  pinMode(RDIR, OUTPUT);
  pinMode(RSPEED, OUTPUT);
  pinMode(LSPEED, OUTPUT);
  pinMode(LDIR, OUTPUT);
  pinMode(RBUMP, INPUT);
  pinMode(LENC, INPUT);
  pinMode(RENC, INPUT);
  pinMode(PAN, OUTPUT);
  pinMode(TILT, OUTPUT);
  pinMode(GRIP, OUTPUT);
  pinMode(FORCE, INPUT);
  pinMode(DIST, INPUT);
  pinMode(LINEM, INPUT);
  pinMode(LINER, INPUT);
  pinMode(LINEL, INPUT);
  
  grip_servo.attach(GRIP);
  pan_servo.attach(PAN);
  tilt_servo.attach(TILT);
  grip_servo.write(40);
  pan_servo.write(90);
  tilt_servo.write(70);
  
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(DIST));
}

void turnR90() {
  analogWrite(RSPEED, 0);
  analogWrite(LSPEED, 0);
  delay(500);
  digitalWrite(RDIR, HIGH);
  digitalWrite(LDIR, LOW);
  
  int state = 0;
  int i = 0;
  analogWrite(RSPEED, 100);
  analogWrite(LSPEED, 100);
  while(true){
    if (digitalRead(RENC) == HIGH && state == 0) {
      i++;
      state = 1;
    }
    if (digitalRead(RENC) == LOW && state == 1) {
      i++;
      state = 0;
    }
    if (i >= 6 && i < 10){
      analogWrite(RSPEED, 80);
      analogWrite(LSPEED, 80);
    }
    if (i >= 10){
      analogWrite(RSPEED, 0);
      analogWrite(LSPEED, 0);
      break;
    }
  }
}

void turnL90() {
  analogWrite(RSPEED, 0);
  analogWrite(LSPEED, 0);
  delay(500);
  digitalWrite(RDIR, LOW);
  digitalWrite(LDIR, HIGH);
  
  int state = 0;
  int i = 0;
  analogWrite(RSPEED, 100);
  analogWrite(LSPEED, 100);
  while(true){
    if (digitalRead(LENC) == HIGH && state == 0) {
      i++;
      state = 1;
    }
    if (digitalRead(LENC) == LOW && state == 1) {
      i++;
      state = 0;
    }
    if (i >= 6 && i < 10){
      analogWrite(RSPEED, 80);
      analogWrite(LSPEED, 80);
    }
    if (i >= 10){
      analogWrite(RSPEED, 0);
      analogWrite(LSPEED, 0);
      break;
    }
  }
}

void driveOnLine(){
  digitalWrite(RDIR, HIGH);
  digitalWrite(LDIR, HIGH);
  if (analogRead(LINEM) >= 800) {
    analogWrite(RSPEED, 100);
    analogWrite(LSPEED, 100);
    Serial.print("going straight\n");
  }
  else if (analogRead(LINER) >= 800 && analogRead(LINEM) < 800) {
    Serial.print("turning right\n");
    while(1) {
      analogWrite(RSPEED, 0);
      analogWrite(LSPEED, 100);
      if (analogRead(LINEM) >= 800){
        analogWrite(RSPEED, 100);
        analogWrite(LSPEED, 100);
        break;
      }
    }  
  }
  else if (analogRead(LINEL) >= 800 && analogRead(LINEM) < 800) {
    Serial.print("turning left\n");
    while(1) {
      analogWrite(RSPEED, 100);
      analogWrite(LSPEED, 0);
      if (analogRead(LINEM) >= 800){
        analogWrite(RSPEED, 100);
        analogWrite(LSPEED, 100);
        break;
      }
    }
  }
}

void driveUntilLeft(){
  while(1){
    digitalWrite(RDIR, HIGH);
    digitalWrite(LDIR, HIGH);
    Serial.println(analogRead(LINEM));
    if (analogRead(LINEM) >= 800) {
      if (analogRead(LINEL) >= 800){
        analogWrite(RSPEED, 0);
        analogWrite(LSPEED, 0);
        delay(500);
        driveForwHalfRot();
        turnL90();
        break;
      }
      else {
        analogWrite(RSPEED, 100);
        analogWrite(LSPEED, 100);
        Serial.print("going straight\n");
      }
    }
    else if (analogRead(LINER) >= 800) {
      Serial.print("turning right\n");
      while(1) {
        analogWrite(RSPEED, 0);
        analogWrite(LSPEED, 100);
        if (analogRead(LINEM) >= 800){
          analogWrite(RSPEED, 100);
          analogWrite(LSPEED, 100);
          break;
        }
      }    
    }
    else if (analogRead(LINEL) >= 800) {
      Serial.print("turning left\n");
      while(1) {
        analogWrite(RSPEED, 100);
        analogWrite(LSPEED, 0);
        if (analogRead(LINEM) >= 800){
          analogWrite(RSPEED, 100);
          analogWrite(LSPEED, 100);
          break;
        }
      }
    }
  }
}

void driveUntilRight(){
  while(1){
    digitalWrite(RDIR, HIGH);
    digitalWrite(LDIR, HIGH);
    Serial.println(analogRead(LINEM));
    if (analogRead(LINEM) >= 800) {
      if (analogRead(LINER) >= 800){
        analogWrite(RSPEED, 0);
        analogWrite(LSPEED, 0);
        delay(500);
        driveForwHalfRot();
        turnR90();
        break;
      }
      else {
        analogWrite(RSPEED, 100);
        analogWrite(LSPEED, 100);
        Serial.print("going straight\n");
      }
    }
    else if (analogRead(LINER) >= 800) {
      Serial.print("turning right\n");
      while(1) {
        analogWrite(RSPEED, 0);
        analogWrite(LSPEED, 100);
        if (analogRead(LINEM) >= 800){
          analogWrite(RSPEED, 100);
          analogWrite(LSPEED, 100);
          break;
        }
      }    
    }
    else if (analogRead(LINEL) >= 800) {
      Serial.print("turning left\n");
      while(1) {
        analogWrite(RSPEED, 100);
        analogWrite(LSPEED, 0);
        if (analogRead(LINEM) >= 800){
          analogWrite(RSPEED, 100);
          analogWrite(LSPEED, 100);
          break;
        }
      }
    }
  }
}

void driveForwHalfRot() {
  analogWrite(RSPEED, 0);
  analogWrite(LSPEED, 0);
  delay(500);
  digitalWrite(RDIR, HIGH);
  digitalWrite(LDIR, HIGH);
  
  int state = 0;
  int i = 0;
  analogWrite(RSPEED, 100);
  analogWrite(LSPEED, 100);
  while(true){
    if (digitalRead(LENC) == HIGH && state == 0) {
      i++;
      state = 1;
    }
    if (digitalRead(LENC) == LOW && state == 1) {
      i++;
      state = 0;
    }
    if (i >= 6 && i < 8){
      analogWrite(RSPEED, 80);
      analogWrite(LSPEED, 80);
    }
    if (i >= 8){
      analogWrite(RSPEED, 0);
      analogWrite(LSPEED, 0);
      break;
    }
  }
}

void driveSkipCorner() {
  while(1){
    digitalWrite(RDIR, HIGH);
    digitalWrite(LDIR, HIGH);
    Serial.println(analogRead(LINEM));
    if (analogRead(LINEM) >= 800) {
      if (analogRead(LINER) >= 800 || analogRead(LINEL) >= 800){
        driveForwHalfRot();
        break;
      }
      else {
        analogWrite(RSPEED, 100);
        analogWrite(LSPEED, 100);
        Serial.print("going straight\n");
      }
    }
    else if (analogRead(LINER) >= 800) {
      Serial.print("turning right\n");
      while(1) {
        analogWrite(RSPEED, 0);
        analogWrite(LSPEED, 100);
        if (analogRead(LINEM) >= 800){
          analogWrite(RSPEED, 100);
          analogWrite(LSPEED, 100);
          break;
        }
      }    
    }
    else if (analogRead(LINEL) >= 800) {
      Serial.print("turning left\n");
      while(1) {
        analogWrite(RSPEED, 100);
        analogWrite(LSPEED, 0);
        if (analogRead(LINEM) >= 800){
          analogWrite(RSPEED, 100);
          analogWrite(LSPEED, 100);
          break;
        }
      }
    }
  }
}

void driveToBall(){
  while(1){
    digitalWrite(RDIR, HIGH);
    digitalWrite(LDIR, HIGH);
    Serial.println(analogRead(LINEM));
    if (analogRead(LINEM) >= 800) {
      analogWrite(RSPEED, 100);
      analogWrite(LSPEED, 100);
      Serial.print("going straight\n");
    }
    else if (analogRead(LINER) >= 800) {
      Serial.print("turning right\n");
      while(1) {
        analogWrite(RSPEED, 0);
        analogWrite(LSPEED, 100);
        if (analogRead(LINEM) >= 800){
          analogWrite(RSPEED, 100);
          analogWrite(LSPEED, 100);
          break;
        }
      }    
    }
    else if (analogRead(LINEL) >= 800) {
      Serial.print("turning left\n");
      while(1) {
        analogWrite(RSPEED, 100);
        analogWrite(LSPEED, 0);
        if (analogRead(LINEM) >= 800){
          analogWrite(RSPEED, 100);
          analogWrite(LSPEED, 100);
          break;
        }
      }
    }
    if (analogRead(DIST) > 200){
      analogWrite(RSPEED, 80);
      analogWrite(LSPEED, 80);
      while(analogRead(DIST) < 620) {}
      analogWrite(RSPEED, 0);
      analogWrite(LSPEED, 0);
      delay(500);
      gripBall();
      break;
    }
  }
}

void gripBall() {
  int grip_angle = 40;
  while(analogRead(FORCE) < 200) {
    grip_angle += 10;
    if (grip_angle >= 150) {
      grip_angle = 40;
    }
    grip_servo.write(grip_angle);
    delay(200);
  }
}
