#include <Wire.h>
#include <MPU6050.h>
#include "thingProperties.h"

#define LED_PIN 2
#define ECHO D6
#define TRIG D7
MPU6050 mp;
float distance;

void setup() {
  Serial.begin(9600);
  delay(1500); 
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  pinMode(LED_PIN, OUTPUT); 
  pinMode(ECHO,INPUT);
  pinMode(TRIG,OUTPUT);

  Wire.begin();
  mp.initialize();
  
  Serial.println(mp.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

}

void loop() {
  ArduinoCloud.update();
  onLed1Change();
  mpustuff();
  getdistance();

  delay(100); 
}

void mpustuff() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  
  mp.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.print("Accelerometer: ");
  Serial.print(ax); Serial.print(", ");
  Serial.print(ay); Serial.print(", ");
  Serial.println(az);

  float mappedValue = map(ax, -32768, 32767, 0, 100); 
  mpu = mappedValue;
  onTextChange();
  
}

void onLed1Change() {
  if (led1) {
    digitalWrite(LED_PIN, HIGH); 
  } else {
    digitalWrite(LED_PIN, LOW);  
  }
}

void onTextChange()  {
  if(mpu<=30){
    text="help";
  }else if(mpu<=50){
    text="cr";
  }else{
    text="food";
  }
}

void getdistance(){
	digitalWrite(TRIG,LOW);
	delay(5);
	digitalWrite(TRIG,HIGH);
	delay(10);
	digitalWrite(TRIG,LOW);
	distance=pulseIn(ECHO,HIGH);
	distance=distance*0.01739;
    ultrasonic=distance;
}