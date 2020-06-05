// Polling 방식 
// touch sensor가 몇번 눌렸는지 정확하게 알기 위해  interrupt
// led가 몇번 켜지는지는 polling 
#include <stdio.h>
#include <wiringPi.h>

#define TOUCH_PIN 6
#define LED_PIN 7

int touch_cnt = 0

void touchPressed() {
	touch_cnt++;
}
 
int main(void) {
	int touch;
	int prev_touch = 0;
	int led_cnt = 0;
	
	if(wiringPiSetup() == -1) return -1;
	pinMode(TOUCH_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);
	
	wiringPiISR(TOUCH_PIN, INT_EDGE_RISING, touchPressed);
	
	while(true) {
		touch = digitalRead(TOUCH_PIN);
		
		if(prev_touch == 0 && touch == 1) {
			digitalWrite(LED_PIN, HIGH);
			led_cnt++;
			delay(1000);
			digitalWrite(LED_PIN, LOW);
			printf("Pressed %d times and Lightened %d times\n", touch_cnt, led_cnt);
		}
		prev_touch = touch;
		delay(100);
	} 
}
