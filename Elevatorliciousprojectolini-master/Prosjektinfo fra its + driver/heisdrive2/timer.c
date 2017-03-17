
#include "timer.h"
#include <time.h>
#include <stdio.h>


static clock_t counterTime;
int timer_on = 0;
int initialTime = 0;

void timerStart(){
 	counterTime = clock();
	timer_on = 1;
}

void timerReset(){
	counterTime = initialTime;
	timer_on = 0;
}

double timeElapsed(){
 	clock_t diff = clock()- counterTime;
  	double time_elapsed = (double)(diff)/CLOCKS_PER_SEC;
  	return time_elapsed;
}