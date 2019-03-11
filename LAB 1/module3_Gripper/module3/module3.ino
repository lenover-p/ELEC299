#include <Servo.h>
Servo grip_servo, pan_servo, tilt_servo;
#define grip_sensor A3
#define led_pin 13


void setup() {
  // put your setup code here, to run once:
  grip_servo.attach(8);
  pan_servo.attach(9);
  tilt_servo.attach(10);
  grip_servo.write(40);
  pan_servo.write(90);
  tilt_servo.write(160);
  pinMode(grip_sensor, INPUT);
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int grip_angle = 40;
  while(analogRead(grip_sensor) < 200) {
    digitalWrite(led_pin, LOW);
    grip_angle += 10;
    if (grip_angle >= 150) {
      grip_angle = 40;
    }
    grip_servo.write(grip_angle);
    delay(200);
  }
  digitalWrite(led_pin, HIGH);
  Serial.print("COMPLETE\n");
  //Serial.print(analogRead(grip_sensor));
  //Serial.print("\n");
}
