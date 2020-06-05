#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define PIN 6
void edge_rise(void);

int main(void){
        
    if(wiringPiSetup() == -1) return 1;
    pinMode(PIN,INPUT);
	wiringPiISR(PIN, INT_EDGE_RISING, edge_rise);
          while(1) {
    	       sleep(1);
	}

}


void edge_rise(void){	
      printf("1");
      exit(0);
}

