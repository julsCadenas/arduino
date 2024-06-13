#include <LiquidCrystal.h>
#include <Servo.h>

// servo motor, lcd, leds

LiquidCrystal lcd(0,1,2,3,4,5);
Servo servo;
float potValue;
int pot=A0;
int r=10;
int y=9;
int g=8;

void setup(){
	lcd.begin(16,2);
	servo.attach(11);
	pinMode(pot,INPUT);
	pinMode(r,OUTPUT);
	pinMode(y,OUTPUT);
	pinMode(g,OUTPUT);
}

void loop(){
	potValue=analogRead(pot);
	potValue=(potValue*180)/1023;
	lcd.setCursor(0,0);
	lcd.print("value: ");
	lcd.setCursor(7,0);
	lcd.print(potValue);
	
	if(potValue<=60){
		lcd.setCursor(0,1);
		lcd.print("critical        ");
		digitalWrite(r,HIGH);
		digitalWrite(y,LOW);
		digitalWrite(g,LOW);
	}else if(potValue<=120){
		lcd.setCursor(0,1);
		lcd.print("warning         ");
		digitalWrite(r,LOW);
		digitalWrite(y,HIGH);
		digitalWrite(g,LOW);
	}else if(potValue<=180){
		lcd.setCursor(0,1);
		lcd.print("safe             ");
		digitalWrite(r,LOW);
		digitalWrite(y,LOW);
		digitalWrite(g,HIGH);
	}else{
		lcd.clear();
		digitalWrite(r,LOW);
		digitalWrite(y,LOW);
		digitalWrite(g,LOW);
	}
	servo.write(potValue);
	delay(30);
}
