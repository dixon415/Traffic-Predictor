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
 * S (Stop) <= 50
 * T (Traffic) <=75
 * O (Overtake) >=150
 */     
#include <Servo.h>

//Servo variables and constants
Servo myservo;
int pos = 0;
int left = 0, right = 0, mid = 0;
int countl = 0, countm = 0, countr = 0;
int leftt = 0, rightt = 0, midt = 0;
int countlt = 0, countmt = 0, countrt = 0;
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
  delay(500);
  serialPrint(45);
  delay(500);
  serialPrint(90);
  delay(500);
  serialPrint(135);
  Serial.println();
}

void serialPrint(int pos){
  myservo.write(pos);
  delay(10);
  value = calculateDistance();
  Serial.print(value);
  Serial.print(",");
  if(pos == 45){
    left = value;
    if((leftt - left <= 10) || (left - leftt <= 10))
    {
      countlt++;
    }
    if(left <= 60)
    {
      countl++;
      if(countl>=5){
        Serial.print("A");
        Serial.print(",");
      }
    }
    else if (left <= 100)
    {
      
      countl++;
      if(countl>=5){
        Serial.print("T");
        Serial.print(",");
      }
    }
    else
    {
      countl = 0;
      countl++;
      if(countl>=5){
        Serial.print("N");
        Serial.print(",");
      }
    }
    leftt = left;
  }
  else if(pos == 90){
    mid = value;
  }
  else if(right == 90){
    right = value;
  }
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
/*void servoRotate()
{
  //Servo rotate from 0 to 180
  for(pos = 0; pos <= 180; pos += 2){
    myservo.write(pos);
    delay(10);
    
    distance = calculateDistance();
    
    //Send Data in the format -> (position, distance)
    Serial.print(pos);
    Serial.print(",");
    Serial.print(distance);
    Serial.println();
  }

  //Servo rotate from 180 to 0
  for(pos = 180; pos >= 0; pos -= 2){
    myservo.write(pos);
    delay(10);
    distance = calculateDistance();
    Serial.print(pos);
    Serial.print(",");
    Serial.print(distance);
    Serial.println();
  }
}*/



