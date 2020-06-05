// Polling ���
// delay(100) : 0.1�� : 10^-3 
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
		touch = digitalRead(PIN_TOUCH);		// ������ 1, �ȴ����� 0 -> �̰� ��ü�� Polling 
		if(touch == 1 && prev_touch == 0) {
			printf("Pressed\n", touch)
			for(j = 0; j < 3; j++) {
				digitalWrite(PIN_LED, HIGH);
				delay(500);
				digitalWrite(PIN_LED, LOW);
				delay(500);
			}
		}
		prev_touch = touch;		// ���� touch�� 0�̵Ǽ� prev_touch�� 0 -> �ٽ� while�� ���� touch = 1, prev_touch = 0 
		delay(100);		// 0.1�� �������� touch ���� �ֱ������� �а� �� 
	}
}
