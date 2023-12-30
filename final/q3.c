#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>
#include <signal.h>

void printAlarm() {
    puts("Alarm!");
}

void setAlarm(int x) {
    alarm(x);
}

void clearAlarm() {
    alarm(0);
}

int main() {
    signal(SIGALRM, printAlarm);
    setAlarm(2); //set 2 sec alarm at 0s, will finish at 2s after execution
    sleep(1);
    setAlarm(6); //set 6 sec alarm at 1s, will finish at 7s after execution
    sleep(1);
    setAlarm(3); //set 3 sec alarm at 2s, will finish at 5s after execution
    sleep(4);
    clearAlarm(); //clear all alarms at 6s after execution
    return 0;
}
