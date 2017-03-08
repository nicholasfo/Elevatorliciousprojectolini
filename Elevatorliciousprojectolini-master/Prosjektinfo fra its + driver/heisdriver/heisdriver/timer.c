

#include <time.h>
#define initialTime = -1;
#define maxTimeOpenDoor = 3;

//time_t is a type from time.h used to store calendar time
//

static time_t counterTime = initialTime;

void timerStart(){

	initialTime = time(NULL);

};

void timerStopp(){

	counterTime = initialTime;

};

//Is time up:
void timeIsUp(){

	if (counterTime < 0){
		return 0;
	}

	time_t now = time(0);

	if (now - counterTime > maxTimeOpenDoor){
		counterTime = initialTime;
		return 1;
	}

	else{
		return 0;
	}

};
