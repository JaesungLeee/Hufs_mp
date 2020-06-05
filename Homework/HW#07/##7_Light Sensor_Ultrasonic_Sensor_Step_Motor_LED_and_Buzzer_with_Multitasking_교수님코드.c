#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#define TRIG 28
#define OUT 29
#define PIN_1A 27
#define PIN_1B 0
#define PIN_2A 1
#define PIN_2B 24
#define DELAY 8000 //7000 //2000
#define LED_PIN 7
#define BUZZER_PIN 15
#define SPI_CH 0
#define ADC_CH 0
#define ADC_CS 29
#define SPI_SPEED 500000
 
void led_on(void) {
	digitalWrite(LED_PIN,HIGH);
} 
 
void led_off(void) {
	digitalWrite(LED_PIN,LOW);
}

void buzzer_on(void) {
	digitalWrite(BUZZER_PIN,HIGH);
}  

void buzzer_off(void) {
	digitalWrite(BUZZER_PIN,LOW);
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

int get_distance() {
    int dis=0, i;
    long start,travel;
    pinMode(OUT,INPUT);
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

int get_light() {
	int value=0;
	unsigned char buf[3];
	pinMode(ADC_CS,OUTPUT);
	buf[0] = 0x06 | ((ADC_CH & 0x04)>>2);
	buf[1] = ((ADC_CH & 0x03)<<6);
    buf[2] = 0x00;
	digitalWrite(ADC_CS,0);
	wiringPiSPIDataRW(SPI_CH,buf,3);
	buf[1]=0x0F & buf[1];
	value=(buf[1] << 8) | buf[2];
	digitalWrite(ADC_CS,1);
	
	return value;
}

void *light_task(void *arg) {
	while(1) {
		int light = get_light();
           
        if(light>=1000){
        	buzzer_off();
		}
		else{
			buzzer_on();
		   	delay(100);
		   	buzzer_off();
		}
		
		delay(100);
	}
}
int main(void) {
    int motor_running=1;
    int ledOn = 0;
    int buzzerOn = 0;
    pthread_t tid;
        
    if(wiringPiSetup() == -1) return 1;
    if(wiringPiSPISetup() == -1) return -1;
        
    pinMode(TRIG,OUTPUT);
    pinMode(PIN_1A,OUTPUT);
    pinMode(PIN_1B,OUTPUT);
    pinMode(PIN_2A,OUTPUT);
    pinMode(PIN_2B,OUTPUT);
    pinMode(LED_PIN,OUTPUT);
    pinMode(BUZZER_PIN,OUTPUT);
        
        pthread_create(&tid, NULL, light_task, NULL);
        stepD();
        
        while(1) {
           int dis = get_distance();
           
           if(dis >= 20 && ledOn == 1){
               printf("%dcm >= 20cm, LED off.\n", dis);
               ledOn = 0;
               led_off();
           }
           if(dis >= 10 && buzzerOn==1){
				  printf("%dcm >= 10cm, Buzzer off.\n", dis);
				  buzzerOn = 0;
				  buzzer_off(); 
           }
           if(dis < 30) {
               if(motor_running==1){
                   printf("%dcm < 30cm, Step Moteor Stopped.\n", dis);
                   motor_running = 0;
               }
               if(dis<20){
                   if(ledOn == 0){
                     printf("%dcm < 20cm, LED On.\n", dis);
                     ledOn = 1;
                     led_on();
                   }
                   if(dis<10){
                     if(buzzerOn == 0){
                       printf("%dcm < 10cm, Buzzer On.\n", dis);
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
