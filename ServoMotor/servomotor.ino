#include <Servo.h>

Servo myservo;
void setup() {
  myservo.attach(7, 500, 2400);
}

void loop() {
  myservo.write(30);
  delay(2000);
  myservo.write(120);
  delay(2000);
}
