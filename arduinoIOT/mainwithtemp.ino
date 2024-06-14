#include <DHT.h>
#include <Wire.h>
#include <MPU6050.h>
#include "thingProperties.h"

#define LED_PIN 2
#define DHTPIN D6
DHT dht11(DHTPIN,DHT11);  

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
}

void loop() {
  ArduinoCloud.update();
  onLed1Change();
  mpustuff();
  gethum();
  delay(100);
}

void mpustuff() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  
  mp.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

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
  if(mpu <= 30){
    text = "help";
  } else if(mpu <= 50){
    text = "cr";
  } else {
    text = "food";
  }
}

void gethum(){
  // int chk = dht.read(DHTPIN);
  hum = dht11.readHumidity();
  temp = dht11.readTemperature(); 
}
