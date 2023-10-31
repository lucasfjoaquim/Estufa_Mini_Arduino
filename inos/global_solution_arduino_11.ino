#include <Servo.h>

const int pinoDHT11 = A0;
const int ldrPin = A2;
const int servoPin1 = 9;
const int motor = 8;
// Defining Variables
int humiditysensorOutput = 0;
int RawValue= 0;
double Voltage = 0;
double tempC = 0;
double tempF = 0;
int lightLevel = 0;
int sensorPHValue = 0;
int valor = 0;

Servo myservo;

void setup(){  
  Serial.begin(9600);
  myservo.attach(servoPin1);  
  pinMode(A1, INPUT);
}

void loop(){
  
  RawValue = analogRead(pinoDHT11);
  Voltage = (RawValue / 1023.0) * 5000; // 5000 to get millivots.
  tempC = (Voltage-500) * 0.1; // 500 is the offset
  lightLevel = analogRead(ldrPin);
  humiditysensorOutput = analogRead(A1);
  sensorPHValue = analogRead(A3);
  float ph = sensorPHValue * (14.0/1023.0);
  int servoAngle = 0;
  if (tempC > 30){
    valor = 130;
    Serial.print("valor: ");
    Serial.print(valor);
  	servoAngle = 90;
    analogWrite(motor,valor);
  }
  else {
    valor = 0;
  	servoAngle = 0;
    analogWrite(motor,valor);
  }
  
  myservo.write(servoAngle); 
  
  Serial.print("Temperature in C = ");
  Serial.print(tempC);
  Serial.print(" Humidity: ");
  Serial.print(map(humiditysensorOutput, 0, 1023, 0, 100));
  
  Serial.print(" Light Level: ");
  Serial.println(lightLevel);
  
  Serial.print("PH do solo : ");
  Serial.println(ph);

  delay(5000);

}