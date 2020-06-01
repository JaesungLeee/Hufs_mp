#include <wiringPi.h>
#include <stdio.h>

#define TOUCH_PIN 6
#define LED_PIN 7

#interrupt, touch_cnt == led_cnt

void edge_rise(void);

int touch_cnt = 0, led_cnt = 0;

int main(void){
    if(wiringPiSetup() == -1) return 1;
    pinMode(TOUCH_PIN,INPUT);
    pinMode(LED_PIN, OUTPUT);
	wiringPiISR(TOUCH_PIN, INT_EDGE_RISING, edge_rise);
	
	while(1){
		delay(10000);
	}
}


void edge_rise(void){
	printf("Pressed.\n");
	touch_cnt++;
	digitalWrite(LED_PIN,HIGH);
	delay(500);
	digitalWrite(LED_PIN,LOW);
	led_cnt++;
	printf("Pressed %d times and Lightened %d times\n", touch_cnt, led_cnt); //I/O buffer 개행문자 만나야 찍기 시작(어느정도 찰때 까지) 
	//fflush(0) 32번째줄에 개행 안쓰고 싶으면. fflush(버퍼를 비워라) , printf부른다음 바로 비워줘야함. 바로바로output하려면 fflush. 
	//file descripter : 0(화면), 1(keyboard)
}
