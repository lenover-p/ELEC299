void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    int code = Serial.read();
    Serial.println((char)code);
    if((char)code == 'Y') {
      Serial.println("Hello World");
    }
  }
}
