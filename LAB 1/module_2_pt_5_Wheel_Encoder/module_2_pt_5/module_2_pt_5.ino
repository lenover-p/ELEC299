#define LSPEED 6
#define RDIR 7
#define RSPEED  5
#define LDIR 4

#define RENCODER 10

int state = 0;
int i = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(RSPEED, OUTPUT);
  pinMode(RDIR, OUTPUT);
  pinMode(LSPEED, OUTPUT);
  pinMode(LDIR, OUTPUT);

  pinMode(RENCODER, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(RDIR, HIGH);
  digitalWrite(LDIR, HIGH);
  analogWrite(RSPEED, 128);
  analogWrite(LSPEED, 128);
  while(i <= 3*20){
    if (digitalRead(RENCODER) == HIGH && state == 0) {
      i++;
      state = 1;
    }
    if (digitalRead(RENCODER) == LOW && state == 1) {
      i++;
      state = 0;
    }
    if (i >= 50){
      analogWrite(RSPEED, 90);
      analogWrite(LSPEED, 90);
    }
  }
  analogWrite(RSPEED, 0);
  analogWrite(LSPEED, 0);

  i = 0;
  delay(500);

  digitalWrite(RDIR, LOW);
  digitalWrite(LDIR, LOW);
  analogWrite(RSPEED, 128);
  analogWrite(LSPEED, 128);
  while(i <= 2*20){
    if (digitalRead(RENCODER) == HIGH && state == 0) {
      i++;
      state = 1;
    }
    if (digitalRead(RENCODER) == LOW && state == 1) {
      i++;
      state = 0;
    }
    if (i >= 30){
      analogWrite(RSPEED, 90);
      analogWrite(LSPEED, 90);
    }
  }

  analogWrite(RSPEED, 0);
  analogWrite(LSPEED, 0);
  
  i = 0;
  delay(500);

  digitalWrite(RDIR, HIGH);
  digitalWrite(LDIR, LOW);
  analogWrite(RSPEED, 128);
  analogWrite(LSPEED, 0);
  while(i <= 16){
    if (digitalRead(RENCODER) == HIGH && state == 0) {
      i++;
      state = 1;
    }
    if (digitalRead(RENCODER) == LOW && state == 1) {
      i++;
      state = 0;
    }
    if (i >= 10){
      analogWrite(RSPEED, 100);
      analogWrite(LSPEED, 100);
    }
  }

  analogWrite(RSPEED, 0);
  analogWrite(LSPEED, 0);
  
  while(1){
    
  }
  /*if (digitalRead(RENCODER) == HIGH && state == 0) {
      i++;
      Serial.print(i);
      Serial.print("\n");
      state = 1;
    }
  if (digitalRead(RENCODER) == LOW && state == 1) {
    i++;
    Serial.print(i);
    Serial.print("\n");
    state = 0;
  }*/
}
