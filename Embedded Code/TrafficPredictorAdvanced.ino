/*This is the code for element14 IoT on wheels design contest traffic predictor project
 * https://www.element14.com/community/community/design-challenges/iot-on-wheels/
 * 
 * Author : Dixon Selvan
 * Date   : November 08, 2017
 * Project: Traffic Predictor and Auto Pilot
 * Website: https://traffic-predictor.000webhostapp.com/
 * 
 * Hardware components
 * -----------------------------------
 * 1. Nucleo-L476RG microcontroller board
 * 2. HC-05 Bluetooth module
 * 3. HC-SR04 Ultrasonic Sensor
 * 4. Servo motor
 * 
 * Nucleo-L476RG  |   Bluetooth module
 * ------------------------------------
 *      5V        |         5V
 *      Gnd       |         Gnd
 *      TX        |         CN3 RX
 *      RX        |         CN3 TX
 *      
 * Servo
 * -----
 * Left = 45 degree
 * Mid = 90 degree
 * Right = 135 degree
 * 
 * A (Alert) <= 60
 * T (Traffic) <=75
 * N (Normal) >=90
 */     
#include <Servo.h>

//Servo variables and constants
Servo myservo;
int pos = 0;
int value = 0;
int servoPin = 3;//Nucleo pin D3

//Ultrasonic sensor variables and constants
int trigPin = 5;//Nucleo pin D5
int echoPin = 2;//Nucleo pin D2

//General variables and constants
long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);  

  Serial.begin(38400);//Serial Connection begin
  
  myservo.attach(servoPin);//Attaching servo pin
}

void loop() {
  // put your main code here, to run repeatedly:
  //servoRotate();
  delay(250);
  serialPrint(45);
  delay(250);
  serialPrint(90);
  delay(250);
  serialPrint(135);
  Serial.println();
}

void serialPrint(int pos){
  myservo.write(pos);
  delay(10);
  value = calculateDistance();
  if(pos==45){
    Serial.print(classifiedData(value));
    Serial.print(",");
  }
  else if(pos==90){
    Serial.print(classifiedData(value));
    Serial.print(",");
  }
  else if(pos==135){
    Serial.print(classifiedData(value));
  }
  else{Serial.print('N');Serial.print(",");}
}

char classifiedData(int value){
  char out=' ';
  if((value<=60)&&(value!=0)){out = 'A';}
  else if((value<=90)&&(value>=75)&&(value!=0))
  {
    out = 'T';
  }
  else{out='N';}
  return out;
}

int calculateDistance()
{
  //Code to calculate Distance from Duration
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(1);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(1);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  return distance;
}
