#include <Wire.h>
#include <MPU6050.h>
#include "thingProperties.h"

#define LED_PIN 2
MPU6050 mp;

void setup() {
  Serial.begin(9600);
  delay(1500); 
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  pinMode(LED_PIN, OUTPUT); 
  
  Wire.begin();
  mp.initialize();
  
  Serial.println(mp.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  // Setup your gauge or display initialization here
}

void loop() {
  ArduinoCloud.update();
  onLed1Change();
  mpustuff();
  

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

  if(mpu<=30){
    text="help";
  }else if(mpu<=50){
    text="cr";
  }else{
    text="food";
  }
  
}

void onLed1Change() {
  if (led1) {
    digitalWrite(LED_PIN, HIGH); 
  } else {
    digitalWrite(LED_PIN, LOW);  
  }
}

/*
  Since Text is READ_WRITE variable, onTextChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTextChange()  {
  // Add your code here to act upon Text change
}