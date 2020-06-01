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

void buzzer_on() {
	digitalWrite(BUZZER_PIN,HIGH);
} 

void buzzer_off() {
	digitalWrite(BUZZER_PIN,LOW);
}

void led_on() {
	digitalWrite(LED_PIN,HIGH);
}

void led_off() {
	digitalWrite(LED_PIN,LOW);
}


void stepD() {
 	digitalWrite(PIN_1A,HIGH);
    digitalWrite(PIN_1B,LOW);
    digitalWrite(PIN_2A,LOW);
    digitalWrite(PIN_2B,LOW);
    delay(1000);
    digitalWrite(PIN_1A,LOW);
    digitalWrite(PIN_1B,HIGH);
    digitalWrite(PIN_2A,LOW);
    digitalWrite(PIN_2B,LOW);
    delay(1000);
    digitalWrite(PIN_1A,LOW);
    digitalWrite(PIN_1B,LOW);
    digitalWrite(PIN_2A,HIGH);
    digitalWrite(PIN_2B,LOW);
    delay(1000);
    digitalWrite(PIN_1A,LOW);
    digitalWrite(PIN_1B,LOW);
    digitalWrite(PIN_2A,LOW);
    digitalWrite(PIN_2B,HIGH);
    delay(1000);  
}

int get_distance(){
	int dis=0, i;
    long start,travel; 
    
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

int main(void){
    int motor_running=1;
    int buzzerOn = 0;
    int ledOn = 0;
    
    if(wiringPiSetup() == -1) return 1;
    
    pinMode(LED_PIN,OUTPUT);
    
    pinMode(BUZZER_PIN,OUTPUT);

    pinMode(TRIG,OUTPUT);
    pinMode(OUT,INPUT);
        
    pinMode(PIN_1A,OUTPUT);
    pinMode(PIN_1B,OUTPUT);
    pinMode(PIN_2A,OUTPUT);
    pinMode(PIN_2B,OUTPUT);
                
    stepD();
    while(1) {
        int dis=get_distance();
        if(dis >= 20 && ledOn == 1) {
        	printf("%dcm >= 20cm. LED Off.", dis);
        	ledOn = 0;
        	led_off();
		}
		
		if(dis >= 10 && buzzerOn == 1) {
        	printf("%dcm >= 10cm. Buzzer Off.", dis);
        	BuzzerOn = 0;
        	Buzzer_off();
		}
		
        if(dis < 30){
            if(motor_running==1){
                printf("%dcm < 30cm, Step Moteor Stopped.\n", dis);
                motor_running = 0;
            }
            if(dis < 20) {
            	if(ledOn == 0) {
            		printf("%dcm < 30cm, LED On.", dis);
            		ledOn = 1;
            		led_on();
				}
				if(dis < 10) {
					if(buzzerOn == 0) {
						printf("%dcm < 10cm. Buzzer On", dis);
						buzzerOn = 1;
						buzzer_on();
					}
				}
			}
        }
        else{ 
            if(motor_running==0){
                printf("%dcm >= 30cm, Step Moteor Resumed.\n", dis);
                motor_running = 1;
            }
            stepD(); 
        }
        delay(100);
    }
}
