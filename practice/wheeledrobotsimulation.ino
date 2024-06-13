#include <Servo.h>

// uses servo motors, ultrasonic, and a buzzer 

Servo servoL;
Servo servoR;
const byte echo=A3;
const byte trig=A2;
float distance;
int buzzer=7;
int r=8;
int g=9;
int y=10;

void setup(){
	Serial.begin(9600);
	servoL.attach(6);
	servoR.attach(5);
	pinMode(echo,INPUT);
	pinMode(trig,OUTPUT);
	pinMode(buzzer,OUTPUT);
	pinMode(r,OUTPUT);
	pinMode(g,OUTPUT);	
	pinMode(y,OUTPUT);	
}

void forward(int d){
	servoL.writeMicroseconds(1300);
	servoR.writeMicroseconds(1700);
	delay(d);
}

void stop(int d){
	servoL.writeMicroseconds(1500);
	servoR.writeMicroseconds(1500);
	delay(d);
}

void turn(int d){
	servoL.writeMicroseconds(1300);
	servoR.writeMicroseconds(1300);
	delay(d);
}

void getdistance(){
	digitalWrite(trig,LOW);
	delay(5);
	digitalWrite(trig,HIGH);
	delay(10);
	digitalWrite(trig,LOW);
	distance=pulseIn(echo,HIGH);
	distance=distance*0.01739;
}

void loop(){
	getdistance();
	delay(10);
	Serial.println(distance);
	
	if(distance<=60){
		digitalWrite(buzzer,HIGH);
		digitalWrite(r,HIGH);
		digitalWrite(g,LOW);
		digitalWrite(y,LOW);
		stop(1000);
		turn(1200);
	}else if(distance<=120){
		digitalWrite(buzzer,LOW);
		digitalWrite(r,LOW);
		digitalWrite(g,LOW);
		digitalWrite(y,HIGH);
	}else if(distance<=180){
		digitalWrite(buzzer,LOW);
		digitalWrite(r,LOW);
		digitalWrite(g,HIGH);
		digitalWrite(y,LOW);
	}else{
		digitalWrite(buzzer,LOW);
		digitalWrite(r,LOW);
		digitalWrite(g,LOW);
		digitalWrite(y,LOW);
		forward(0);
	}
}




