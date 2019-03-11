#define ENCODER 10
#define LED 12

int state = 0;
int i = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ENCODER, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  
  //Serial.print(digitalRead(ENCODER));
  if (digitalRead(ENCODER) == HIGH) {
    digitalWrite(LED, HIGH);
    state = 1;
  }
  else {
    digitalWrite(LED, LOW);
    if (state == 1) {
      i++;
      Serial.print(i);
      Serial.print("\n");
      state = 0;
    }
  }
  if (i >= 16) {
    for (i=0; i<4; i++){
      digitalWrite(LED, HIGH);
      delay(500);
      digitalWrite(LED, LOW);
      delay(500);
    }
    i = 0;
    
  }


  /*int i = 0;
  while(i < 16){
    if (digitalRead(ENCODER) == HIGH) {
      while(1){
        if(digitalRead(ENCODER) == LOW){
          i++;
          Serial.print(i);
          Serial.print("\n");
          break;
        }
      }
    }
  }
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);*/
}
