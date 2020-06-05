//polling switch&buzzer
//Switch -> 0 : pressed, 1 : unpressed
#include <wiringPi.h>
#include <stdio.h>

#define BUZZER_PIN 15
#define SWITCH_PIN 3

int switchCount = 0;

void switchPressed(){
	switchCount++;	
}

int main(void){
	int buzzerCount = 0;
	int sw;
    int prev_sw = 1;
        
    if(wiringPiSetup() == -1) return 1;
    pinMode(SWITCH_PIN,INPUT);
	pinMode(BUZZER_PIN,OUTPUT);
	wiringPiISR(SWITCH_PIN, INT_EDGE_FALLING, switchPressed);

	while(1){
		sw = digitalRead(SWITCH_PIN);
		if(sw == 0 && prev_sw == 1){
			digitalWrite(BUZZER_PIN,HIGH);
			delay(1000);
			digitalWrite(BUZZER_PIN,LOW);
			buzzerCount++;
			printf("Pressed %d times and Buzzed %d times\n", switchCount, buzzerCount);
		}
		delay(100);
		prev_sw = sw;
	}
}
