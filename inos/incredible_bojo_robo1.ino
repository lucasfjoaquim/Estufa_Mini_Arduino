#include <Servo.h>

const int servoPin = 9;       
const int photoresistorPin = A0;  

Servo myservo;

void setup() {
  myservo.attach(servoPin);  
  Serial.begin(9600);       
}

void loop() {
  int lightValue = analogRead(photoresistorPin); 

 
  int servoAngle = map(lightValue, 0, 1023, 0, 180);

  myservo.write(servoAngle);  

  Serial.print("Valor lido: ");
  Serial.print(lightValue);
  Serial.print(", Ângulo do servo: ");
  Serial.println(servoAngle);

  delay(100);  
}
