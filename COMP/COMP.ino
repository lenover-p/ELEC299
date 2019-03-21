#include <Servo.h>
#include <QSerial.h>
Servo grip_servo, pan_servo, tilt_servo;
QSerial myIRserial;


#define IRTX -1
#define LENC 2
#define LBUMP 3
#define RDIR 4
#define RSPEED 5
#define LSPEED 6
#define LDIR 7
#define RBUMP 8
#define TILT 9
#define GRIP 10
#define PAN 11
#define IRRX 12
#define RENC 13
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
  pinMode(RDIR, OUTPUT);
  pinMode(RSPEED, OUTPUT);
  pinMode(LSPEED, OUTPUT);
  pinMode(LDIR, OUTPUT);
  pinMode(RBUMP, INPUT);
  pinMode(LENC, INPUT);
  pinMode(RENC, INPUT);
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
  tilt_servo.write(60);

  myIRserial.attach(IRRX, IRTX);
  
  Serial.begin(9600);
}

void loop() {
  DriveSkipCorner();
  DriveSkipCorner();
  DriveSkipCorner();
  DriveUntilLeft();
  DriveSkipCorner();
  DriveSkipCorner();
  DriveToBall();
  TurnL180();
  DriveSkipCorner();
  DriveSkipCorner();
  DriveUntilRight();
  DriveSkipCorner();
  DriveSkipCorner();
  DriveSkipCorner();
  DriveToGoal();
  break;
}

void TurnR90() {
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
  if (analogRead(LINEL) < 800 && analogRead(LINEM) < 800 && analogRead(LINER) < 800){
  analogWrite(RSPEED, 80);
  analogWrite(LSPEED, 80);
  while(analogRead(LINEL) < 800 && analogRead(LINEM) < 800 && analogRead(LINER) < 800){}
  analogWrite(RSPEED, 0);
  analogWrite(LSPEED, 0);
  }
}

void TurnL90() {
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
  if (analogRead(LINEL) < 800 && analogRead(LINEM) < 800 && analogRead(LINER) < 800){
  analogWrite(RSPEED, 80);
  analogWrite(LSPEED, 80);
  while(analogRead(LINEL) < 800 && analogRead(LINEM) < 800 && analogRead(LINER) < 800){}
  analogWrite(RSPEED, 0);
  analogWrite(LSPEED, 0);
  }
}

void TurnL180() {
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
    if (i >= 15 && i < 20){
      analogWrite(RSPEED, 80);
      analogWrite(LSPEED, 80);
    }
    if (i >= 20){
      analogWrite(RSPEED, 0);
      analogWrite(LSPEED, 0);
      break;
    }
  }
  if (analogRead(LINEL) < 800 && analogRead(LINEM) < 800 && analogRead(LINER) < 800){
    analogWrite(RSPEED, 80);
    analogWrite(LSPEED, 80);
    while(analogRead(LINEL) < 800 && analogRead(LINEM) < 800 && analogRead(LINER) < 800){}
    analogWrite(RSPEED, 0);
    analogWrite(LSPEED, 0);
  }
}

void DriveOnLine(int topSpeed){
  digitalWrite(RDIR, HIGH);
  digitalWrite(LDIR, HIGH);
  if (analogRead(LINEM) >= 800) {
    analogWrite(RSPEED, topSpeed);
    analogWrite(LSPEED, topSpeed);
    Serial.print("going straight\n");
  }
  else if (analogRead(LINER) >= 800 && analogRead(LINEM) < 800) {
    Serial.print("turning right\n");
    while(1) {
      analogWrite(RSPEED, 0);
      analogWrite(LSPEED, 100);
      if (analogRead(LINEM) >= 800){
        analogWrite(RSPEED, topSpeed);
        analogWrite(LSPEED, topSpeed);
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
        analogWrite(RSPEED, topSpeed);
        analogWrite(LSPEED, topSpeed);
        break;
      }
    }
  }
}

void DriveUntilLeft(){
  while(1){
    digitalWrite(RDIR, HIGH);
    digitalWrite(LDIR, HIGH);
    Serial.println(analogRead(LINEM));
    if (analogRead(LINEM) >= 800) {
      if (analogRead(LINEL) >= 800){
        analogWrite(RSPEED, 0);
        analogWrite(LSPEED, 0);
        delay(500);
        DriveForwHalfRot();
        TurnL90();
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

void DriveUntilRight(){
  while(1){
    digitalWrite(RDIR, HIGH);
    digitalWrite(LDIR, HIGH);
    Serial.println(analogRead(LINEM));
    if (analogRead(LINEM) >= 800) {
      if (analogRead(LINER) >= 800){
        analogWrite(RSPEED, 0);
        analogWrite(LSPEED, 0);
        delay(500);
        DriveForwHalfRot();
        TurnR90();
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

void DriveForwHalfRot() {
  //analogWrite(RSPEED, 0);
  //analogWrite(LSPEED, 0);
  //delay(500);
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

void DriveBack() {
  analogWrite(RSPEED, 0);
  analogWrite(LSPEED, 0);
  delay(500);
  digitalWrite(RDIR, LOW);
  digitalWrite(LDIR, LOW);
  
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
    if (i >= 19 && i < 24){
      analogWrite(RSPEED, 80);
      analogWrite(LSPEED, 80);
    }
    if (i >= 24){
      analogWrite(RSPEED, 0);
      analogWrite(LSPEED, 0);
      break;
    }
  }
}

void DriveSkipCorner() {
  while(1){
    digitalWrite(RDIR, HIGH);
    digitalWrite(LDIR, HIGH);
    Serial.println(analogRead(LINEM));
    if (analogRead(LINEM) >= 800) {
      if (analogRead(LINER) >= 800 || analogRead(LINEL) >= 800){
        DriveForwHalfRot();
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

void DriveToBall(){
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
    while(1){
      DriveOnLine(80);
      if(analogRead(DIST) > 620){
        analogWrite(RSPEED, 0);
        analogWrite(LSPEED, 0);
        delay(500);
        if (analogRead(LINEM) < 800) {
          DriveBack();
        }
        else{
          GripBall();
          return;
        }
      }
    }
  }
}

void DriveToGoal(){
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
    while(1){
      DriveOnLine(100);
      if(digitalRead(LBUMP) == LOW || digitalRead(RBUMP) == LOW){
        while(1){
          if(digitalRead(LBUMP) == LOW && digitalRead(RBUMP) == LOW){
            break;
          }
        }
        analogWrite(RSPEED, 0);
        analogWrite(LSPEED, 0);
        delay(500);
        DropBall();
        return;
      }
    }
  }
}

void GripBall() {
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

void DropBall() {
  int grip_angle = 40;
  grip_servo.write(grip_angle);
  delay(200);
}

int GetStartPos() {
  while(1) {
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
      if (val == 1){
        return 1;
      }
      else if (val == 2) {
        return 2;
      }
      else if (val == 3) {
        return 3;
      }
    }
  }
}
