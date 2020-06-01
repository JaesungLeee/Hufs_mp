// Polling ��� 
#include <stdio.h>
#include <wiringPi.h>

#define TOUCH_PIN 6
#define LED_PIN 7

int main(void) {
	int prev_touch = 0, touch, i, led_state = 0
	
	if(wiringPiSetup() == -1) return 1;
	pinMode(TOUCH_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);
	
	while(1) {
		touch = digitalRead(TOUCH_PIN);		 // digitalRead�� �� ���� ������ 1, ���� 0 
		if(touch && !prev_touch) {			 // touch�� 1�̰� prev_touch�� 1�̸� �� ������ �ִ°� 
			printf("PRESSED\n");
			if(led_state == 0) {
				digitalWrite(LED_PIN, HIGH);
				led_state == 1;
			}
			else {
				digitalWrite(LED_PIN, LOW);
				led_state == 0;
			}
		}
		// ���⼭ ���� 0.1�� �������� �ֱ������� ����		
		prev_touch = touch;
		delay(100);
	}
}
