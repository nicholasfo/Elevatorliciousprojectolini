#include "channels.h"
#include "koesystem.h"
#include "fsm.h"
#include "elev.h"
#include "timer.h"
#include <stdio.h>


int direction = 0;		// -1 = ned, 0 = stop, 1 = opp
int lastFloor;			// 0 = 1.etg, 1 = 2.etg, 2 = 3.etg, 3 = 4.etg
int nextFloor;			
int lastDirection;		


void fsmInit(){
	elev_init();
	timerReset();
	lastDirection = -1;
	elev_set_door_open_lamp(0);
	if(elev_get_floor_sensor_signal() == -1) {
		elev_set_motor_direction(DIRN_DOWN);
		
	while(1){
		lastFloor = elev_get_floor_sensor_signal();
		if(lastFloor != -1) {

			elev_set_motor_direction(DIRN_STOP);
			elev_set_floor_indicator(lastFloor);
			printf("lastFloor %d\n", lastFloor);
			
			break;

			}
		}

	}
}



void fsmTakeOrders() {
	for (int i = 0; i < 4; i++) {
		if (i != 3) {
			if (elev_get_button_signal(BUTTON_CALL_UP, i) == 1) {
				queueAdd(arrayUp, i);
				elev_set_button_lamp(BUTTON_CALL_UP, i,1);
			}
		}
		if (i != 0) {
			if (elev_get_button_signal(BUTTON_CALL_DOWN, i) == 1) {
				queueAdd(arrayDown, 3-i);
				elev_set_button_lamp(BUTTON_CALL_DOWN, i, 1);
			}
		}
		
		if (elev_get_button_signal(BUTTON_COMMAND, i) == 1) {
			elev_set_button_lamp(BUTTON_COMMAND, i, 1);
			if (i != 0){
				queueAdd(arrayDown, 3-i);

			}
			if (i != 3){
				queueAdd(arrayUp, i);
			}
		}
	}
}


void fsmStop(){
	queueClear();
	timerReset();
	elev_clear_all_lamps();
	elev_set_motor_direction(DIRN_STOP);
	
	while(elev_get_stop_signal()){
		elev_set_stop_lamp(1);
	}
	elev_set_stop_lamp(0);
	return;
}


void fsmRun(){

	int floor = elev_get_floor_sensor_signal();
	nextFloor = queueGetNextFloor(lastDirection, lastFloor);
	direction = queueGetNextDir(lastDirection, lastFloor);

	if(direction == 1) {
		elev_set_motor_direction(DIRN_UP);
		lastDirection = 1;
	}
		
	if(direction == -1) {
		elev_set_motor_direction(DIRN_DOWN);
		lastDirection = -1;
	}

	printf("%d, %d, %d, %d\n", lastFloor + 1, lastDirection, nextFloor + 1, direction);
	
	if(floor == -1){		//Returns if elevator not in a floor
		return;
	}
	
	elev_set_floor_indicator(lastFloor);
	lastFloor = floor;
	return;
	
}	


void fsmStopAtFloor(){
	if((nextFloor == lastFloor) && (direction == 0) && (timer_on == 0)){
		timerStart();
	}

	if((nextFloor == lastFloor) && (direction == 0)) {
		elev_set_door_open_lamp(1);
		elev_clear_lamps(lastFloor);
		elev_set_motor_direction(DIRN_STOP);
		queuePopFloor(nextFloor);
    }
    
    if(timeElapsed() >= 3){
    	printf("timeElapsed: %le\n", timeElapsed());
    	timerReset();
		elev_set_door_open_lamp(0);
    }
}