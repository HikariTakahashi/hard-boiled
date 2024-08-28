// Arduino Uno R4ではVarSpeedServoライブラリが使用できない。

#include <VarSpeedServo.h>
VarSpeedServo myservo;
 
void setup() {
  
  myservo.attach(13);
  
} 
 
void loop() {
  
  myservo.write(0, 45, true);
  myservo.write(180, 45, true);
  
}