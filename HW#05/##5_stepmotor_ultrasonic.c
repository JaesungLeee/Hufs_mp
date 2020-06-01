#include <stdio.h>
#include <wiringPi.h>

#define TRIG 28
#define OUT 29

#define PIN_1A 27
#define PIN_1B 0
#define PIN_2A 1
#define PIN_2B 24

void motor() {
	digitalWrite(PIN_1A,HIGH);
    digitalWrite(PIN_1B,LOW);
	digitalWrite(PIN_2A,LOW);
	digitalWrite(PIN_2B,LOW);
    usleep(1000);
    digitalWrite(PIN_1A,LOW);
    digitalWrite(PIN_1B,HIGH);
    digitalWrite(PIN_2A,LOW);
    digitalWrite(PIN_2B,LOW);
    usleep(1000);
    digitalWrite(PIN_1A,LOW);
    digitalWrite(PIN_1B,LOW);
    digitalWrite(PIN_2A,HIGH);
    digitalWrite(PIN_2B,LOW);
    usleep(1000);
    digitalWrite(PIN_1A,LOW);
    digitalWrite(PIN_1B,LOW);
    digitalWrite(PIN_2A,LOW);
    digitalWrite(PIN_2B,HIGH);
    usleep(1000);
}

int main(void){
    int dis=0, i;
    long start,travel;
    int i=0;

    if(wiringPiSetup() == -1) return 1;

    pinMode(TRIG,OUTPUT);
    pinMode(OUT,INPUT);
        
    pinMode(PIN_1A,OUTPUT);
    pinMode(PIN_1B,OUTPUT);
    pinMode(PIN_2A,OUTPUT);
    pinMode(PIN_2B,OUTPUT);

			
    while(1) {	
    	digitalWrite(TRIG,0);
        usleep(2);
        digitalWrite(TRIG,1);
        usleep(20);
        digitalWrite(TRIG,0);

        while(digitalRead(OUT) == 0);

        start = micros();

        while(digitalRead(OUT) == 1);

        travel = micros() - start;

        dis = travel / 58;

        if (dis < 30) {
            printf("%dcm < 30cm, Step Mottor Stopped", dis);
            // motor()를 안부르면 안돌아감 
            	
		}
		else {
			motor();	
			print("%dcm >= 30cm, Step Motter Resumed", dis);
		}
        delay(100);
    }        
}



/*
int ultrasonic() {
digitalWrite(TRIG,0);
        usleep(2);
        digitalWrite(TRIG,1);
        usleep(20);
        digitalWrite(TRIG,0);

        while(digitalRead(OUT) == 0);

        start = micros();

        while(digitalRead(OUT) == 1);

        travel = micros() - start;

        dis = travel / 58;
        
        return dis;
    }
    */

 
 
