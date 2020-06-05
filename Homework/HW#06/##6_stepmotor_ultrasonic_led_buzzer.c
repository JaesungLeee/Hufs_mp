(��) 25cm < 30cm, Step Motor Stopped.
Step motor�� �����Ǿ� �ִٰ� �Ÿ� x�� 30cm �̻��� �Ǹ�  'xcm >= 30cm, Step Motor Resumed.' ��� ����ϰ�, �ٽ� step motor�� ���ư���. 
(��) 40cm >= 30cm, Step Motor Resumed.
x�� 20cm �̸��̸� 'xcm < 20cm, LED On.' ��� ����ϰ�,  LED�� �Ҵ�.
(��) 17cm < 20cm, LED On.
LED�� ���� �ִٰ� x�� 20cm �̻��� �Ǹ�  'xcm >= 20cm, LED Off.' ��� ����ϰ�, �ٽ� LED�� ����.
(��) 24cm >= 20cm, LED Off.
x�� 10cm �̸��̸� 'xcm < 10cm, Buzzer On.' ��� ����ϰ�,  buzzer�� �︰��.
(��) 3cm < 10cm, Buzzer On.
Buzzer�� �︮�ٰ� x�� 10cm �̻��� �Ǹ� 'xcm >= 10cm, Buzzer Off.' ��� ����ϰ�, �ٽ� buzzer�� ����.
(��) 12cm >= 10cm, Buzzer Off.
 

#include <stdio.h>
#include <wiringPi.h>

#define LED_PIN 7

#define BUZZER_PIN 15

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

void buzzer() {
	int i;
	for(i=0; i<10; i++) {
	    digitalWrite(BUZZER_PIN,HIGH);
    	delay(200);
    	digitalWrite(BUZZER_PIN,LOW);
    	delay(200);
	}   
}

void led_pin() {
	int i;
	for(i=0; i< 10; i++) {

      digitalWrite(LED_PIN,HIGH);

      delay(500);

      digitalWrite(LED_PIN,LOW);

      delay(500);

   }   
}

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

   if (dis < 30) {
        printf("%dcm < 30cm, Step Mottor Stopped", dis);
        if (dis < 20) {
        	led_pin();
        	printf("%dcm < 20cm. LED On", dis);

        	if(dis < 10) {
        		buzzer();
        		printf("%dcm < 10cm. Buzzer On", dis);
			}
			else {
				printf("%dcm >= 10cm. Buzzer Off", dis);
			}
		}
		else {
			printf("%dcm >= 20cm. LED Off", dis);
		}
        // motor()�� �Ⱥθ��� �ȵ��ư� 
            	
	}
	else {
		motor();	
		print("%dcm >= 30cm, Step Motter Resumed", dis);
	}
    delay(100);
		
}



int main(void){
    int dis=0, i;
    long start,travel;
    int i=0;

    if(wiringPiSetup() == -1) return 1;
    
    pinMode(LED_PIN,OUTPUT);
    
    pinMode(BUZZER_PIN,OUTPUT);

    pinMode(TRIG,OUTPUT);
    pinMode(OUT,INPUT);
        
    pinMode(PIN_1A,OUTPUT);
    pinMode(PIN_1B,OUTPUT);
    pinMode(PIN_2A,OUTPUT);
    pinMode(PIN_2B,OUTPUT);

	ultrasonic();
	
	
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

 
 
