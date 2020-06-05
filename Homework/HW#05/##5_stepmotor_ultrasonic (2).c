//mp5
//프로그램을 수행하기 시작하면 step motor는 정상 회전으로 계속 돌아가야 한다.  
//Ultrasonic Sensor로 주변과의 거리 x를 0.1s 간격으로 측정한다. 
//측정된 거리 x가 30cm 미만이면 'xcm < 30cm, Step Motor Stopped.' 라고 출력하고,  step motor를 중지시킨다.
//(예) 25cm < 30cm, Step Motor Stopped.
//Step motor가 중지되어 있다가 거리 x가 30cm 이상이 되면  'xcm >= 30cm, Step Motor Resumed.' 라고 출력하고, 다시 step motor가 돌아간다. 
//(예) 40cm >= 30cm, Step Motor Resumed.

#include <stdio.h>
#include <wiringPi.h>
#define TRIG 28
#define OUT 29
#define PIN_1A 27
#define PIN_1B 0
#define PIN_2A 1
#define PIN_2B 24
#define DELAY 8000 //7000 //2000

void stepMotor() {
	digitalWrite(PIN_1A, HIGH);
	digitalWrite(PIN_1B, LOW);
	digitalWrite(PIN_2A, LOW);
    digitalWrite(PIN_2B, LOW);
    delay(1000);
    digitalWrite(PIN_1A, LOW);
    digitalWrite(PIN_1B, HIGH);
    digitalWrite(PIN_2A, LOW);
    digitalWrite(PIN_2B, LOW);
    delay(1000);
    digitalWrite(PIN_1A, LOW);
    digitalWrite(PIN_1B, LOW);
    digitalWrite(PIN_2A, HIGH);
    digitalWrite(PIN_2B, LOW);
    delay(1000);
    digitalWrite(PIN_1A, LOW);
    digitalWrite(PIN_1B, LOW);
    digitalWrite(PIN_2A, LOW);
    digitalWrite(PIN_2B, HIGH);
    delay(1000);
}

int ultrasonic(){
    int dis = 0;
    long start, travel; 
    
    digitalWrite(TRIG,0);
    usleep(2);
    digitalWrite(TRIG,1);
    usleep(20);
    digitalWrite(TRIG,0);
    
    while(digitalRead(OUT) == 0);
    start = micros();
    while(digitalRead(OUT) == 1);
    
	travel = micros() - start;
    dis = travel / 58;
    
	return dis;
}

int main(void){
    int motor_running = 1;
    
    if(wiringPiSetup() == -1) return 1;
    pinMode(TRIG,OUTPUT);
    pinMode(OUT,INPUT);
    pinMode(PIN_1A,OUTPUT);
    pinMode(PIN_1B,OUTPUT);
    pinMode(PIN_2A,OUTPUT);
    pinMode(PIN_2B,OUTPUT);
                
    stepMotor();
    while(1) {
        dis = ultrasonic();
        
        if(dis < 30) {
            if(motor_running == 1) {
                printf("%dcm < 30cm, Step Moteor Stopped.\n", dis);
                motor_running = 0;
            }
        }
        else { 
        	if(motor_running == 0) {
            	printf("%dcm >= 30cm, Step Moteor Resumed.\n", dis);
                motor_running = 1;
            }
            stepMotor(); 
        }
        delay(100);
    }
}
