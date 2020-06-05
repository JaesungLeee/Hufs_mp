#include <stdio.h>

#define BUF_SIZE 100

int main(void){
    FILE *fp;
    char str[BUF_SIZE];
    fp = fopen("/home/pi/ksaehwa/log/lightLog.txt", "r");
    if (fp == NULL) printf("file open error!!");
    fread(str, 1, BUF_SIZE, fp);
    printf("%s", str);
    fclose(fp);
}
