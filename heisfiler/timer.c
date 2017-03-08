

#include <time.h>
#include "timer.h"
#define initialTime = -1;

static time_t g_startTime = initialTime;

void startTimer(){
	g_startTime = time(0);
}

void stopTimer(){

	g_startTime = initialTime;
}

int isTimerTimeout(){

	if (g_startTime < 0){ 								//if timer isnt running, return bullshit
		
		return -1;
	}

	time_t now = time(0);

	if (now - g_startTime > 3){

		return 1; 										//timer is finished

	}

	else {

		return 0; 										//timer is running 

	}

}
