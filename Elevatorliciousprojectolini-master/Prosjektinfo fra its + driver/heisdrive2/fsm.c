//Tilstandsmaskin for denne supre haisen som er kodet av to tullinger som liker sushi og sake bedre enn å ta heis.
#include "channels.h"
#include "koesystem.h"
#include "fsm.h"
#include "elev.h"
#include <stdio.h>


int direction = 0;			// -1 = ned, 0 = stop, 1 = opp
int lastFloor;			// 0 = 1.etg, 1 = 2.etg, 2 = 3.etg, 3 = 4.etg
int nextFloor;
int lastDirection;			//

//Start state-machine:
void fsmStart(){
	elev_init();
	lastDirection = -1;
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
	//queuePrint();
}

//Stop state-machine:

void fsmStop(){
	queueClear();
	elev_button_type_t button_type;
    for(button_type = BUTTON_CALL_UP; button_type <= BUTTON_COMMAND; button_type++){
        for(int floor = 0; floor < 4; floor++){
            if(!((button_type == BUTTON_CALL_UP && floor == 3) || (button_type == BUTTON_CALL_DOWN && floor == 0))){
                elev_set_button_lamp(button_type, floor, 0);
            }
        }
    }
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
		//printf("Retningen blir satt oppover \n");
		elev_set_motor_direction(DIRN_UP);
		lastDirection = 1;
			
	}
		

	if(direction == -1) {
		//printf("Retningen blir satt nedover \n");
		elev_set_motor_direction(DIRN_DOWN);
		lastDirection = -1;
	}

	printf("%d, %d, %d, %d\n", lastFloor + 1, lastDirection, nextFloor + 1, direction);
	if(floor == -1){
		return;
	}
	lastFloor = floor;
	//nextFloor = queueGetNextFloor(lastDirection, lastFloor);
	
	//direction = queueGetNextDir(lastDirection, lastFloor);
	//printf("%d, %d, %d, %d\n", lastFloor + 1, lastDirection, nextFloor + 1, direction);
	//printf("LastFloor %d\n", lastFloor);
	


	
	
	if(nextFloor == lastFloor) {
		elev_set_motor_direction(DIRN_STOP);
		queuePopFloor(nextFloor);
    	elev_set_button_lamp(BUTTON_COMMAND, lastFloor, 0);
    	switch(lastFloor){
	        case 0:
	            elev_set_button_lamp(BUTTON_CALL_UP, 0, 0);
	            break;
	        case 1:
	            elev_set_button_lamp(BUTTON_CALL_UP, 1, 0);
	            elev_set_button_lamp(BUTTON_CALL_DOWN, 1, 0);
	            break;
	        case 2:
	            elev_set_button_lamp(BUTTON_CALL_UP, 2, 0);
	            elev_set_button_lamp(BUTTON_CALL_DOWN, 2, 0);
	            break;
	        case 3:
	            elev_set_button_lamp(BUTTON_CALL_DOWN, 3, 0);
	            break;
	        default:
	            break;
    	}
	}
	return;
	
}	

/*
void fsmStopAtFloor(int floor) {

	if(elev_get_floor_sensor_signal() == nextFloor){
		elev_set_floor_indicator(lastFloor);
		elev_set_motor_direction(DIRN_STOP);
		lastFloor = nextFloor;
		queuePopFloor(arrayUp, nextFloor);
		queuePopFloor(arrayDown, nextFloor-1);
		nextFloor = queueGetNextFloor(arrayDown, arrayUp, fsmSetDirection());

	}
	//Heisen oppdager at den kommer til en etasje
	if (lastFloor != floor && floor != -1) {
		lastFloor = floor;
		elev_set_floor_indicator(lastFloor);

		//Funksjonen sjekker om etasjen den nå har kommet til er den samme som correctFloor returnerer.  
		if (fsmCorrectFloor(lastFloor, direction) == lastFloor) {
			elev_set_motor_direction(DIRN_STOP);
			direction = DIRN_STOP;
			queuePopFloor(arrayUp, lastFloor);
			queuePopFloor(arrayDown, lastFloor);
			//timerStart();
			
			while (timeIsUp() == 0) {

				elev_set_door_open_lamp(1);		//Funker dette, eller må den settes lav igjen etter while er ferdig? idk

			}
			elev_set_door_open_lamp(0);
			
		}

	}
}
*/
