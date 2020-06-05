#include <wiringPi.h>
#include <stdio.h>

#define PIN 3

void get_switch(void) {
    printf("Pressed!!");
    exit(0);
}

int main(void){
    if(wiringPiSetup() == -1) return 1;
    pinMode(PIN,INPUT);

    wiringPiISR(PIN, INT_EDGE_FALLING, get_switch);
    while(1) {
        sleep(1);
    }
}