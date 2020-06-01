#include <stdio.h>
#include <wiringPi.h>

#define TOUCH_PIN 6
#define LED_PIN 7

void edge_rise(void);

void edge_fall(void);

int main(void) {
	if(wiringPiSetup() == -1) return 1;
	pinMode(TOUCH_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);
	
	wiringPiISR(TOUCH_PIN, INT_EDGE_RISING, edge_rise);
	wiringPiISR(TOUCH_PIN, INT_EDGE_FALLING, edge_fall);
	
	delay(10000);		// ������ interrupt ��ȣ ���� �ſ��� delay ����� �� 
}

void edge_rise(void) {
	digitalWrite(LED_PIN, HIGH);
	delay(1000);	// 1�� ���� ���� 
	wiringPiISR(TOUCH_PIN, INT_EDGE_FALLING, edge_fall);		// edge_fall �Լ��� ���� LED�� ���� 
	printf("Edge_rised\n");
} 

void edge_fall(void) {
	digitalWrite(LED_PIN, LOW); 
	wiringPiISR(TOUCH_PIN, INT_EDGE_RISING, edge_rise);		// edge_rise �Լ��� ���� LED�� ���� 
	printf("Edge_falled\n");
}
