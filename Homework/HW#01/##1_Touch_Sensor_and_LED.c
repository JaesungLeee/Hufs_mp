// Polling 방식
// delay(100) : 0.1초 : 10^-3 
#include <stdio.h>
#include <wiringPi.h>

#define PIN_LED 7
#define PIN_TOUCH 6

int main(void) {
	int touch = 0, prev_touch = 0, i, j;
	
	if (wiringPiSetup() == -1) return 1;
	pinMode(PIN_TOUCH, INPUT);
	pinMode(PIN_LED, OUTPUT);
	
	while(1) {
		touch = digitalRead(PIN_TOUCH);		// 누르면 1, 안누르면 0 -> 이거 자체가 Polling 
		if(touch == 1 && prev_touch == 0) {
			printf("Pressed\n", touch)
			for(j = 0; j < 3; j++) {
				digitalWrite(PIN_LED, HIGH);
				delay(500);
				digitalWrite(PIN_LED, LOW);
				delay(500);
			}
		}
		prev_touch = touch;		// 때면 touch가 0이되서 prev_touch가 0 -> 다시 while문 돌때 touch = 1, prev_touch = 0 
		delay(100);		// 0.1초 간격으로 touch 값을 주기적으로 읽게 됨 
	}
}
