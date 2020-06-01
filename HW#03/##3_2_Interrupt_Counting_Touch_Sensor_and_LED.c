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
	printf("Pressed %d times and Lightened %d times\n", touch_cnt, led_cnt); //I/O buffer ���๮�� ������ ��� ����(������� ���� ����) 
	//fflush(0) 32��°�ٿ� ���� �Ⱦ��� ������. fflush(���۸� �����) , printf�θ����� �ٷ� ��������. �ٷιٷ�output�Ϸ��� fflush. 
	//file descripter : 0(ȭ��), 1(keyboard)
}
