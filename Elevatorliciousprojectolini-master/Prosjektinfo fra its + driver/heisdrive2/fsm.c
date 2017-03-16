//Tilstandsmaskin for denne supre haisen som er kodet av to tullinger som liker sushi og sake bedre enn å ta heis.
#include "channels.h"
#include "koesystem.h"
#include "fsm.h"
#include "elev.h"
#include <stdio.h>


int direction = -2;			// -1 = ned, 0 = stop, 1 = opp
int lastFloor;			// 0 = 1.etg, 1 = 2.etg, 2 = 3.etg, 3 = 4.etg
int nextFloor;
int lastDirection;			//

//Start state-machine:
void fsmStart(){
	elev_init();
	if(elev_get_floor_sensor_signal() == -1) {
		elev_set_motor_direction(DIRN_DOWN);
		direction = -1;
		
	while(1){
		if(elev_get_floor_sensor_signal() != -1) {
			lastFloor = elev_get_floor_sensor_signal();
			elev_set_motor_direction(DIRN_STOP);
			elev_set_floor_indicator(lastFloor);
			printf("lastFloor %d\n", lastFloor);
			direction = 0;
			break;

			}
		}

	}
	/*
	if(elev_get_floor_sensor_signal() != -1){
		elev_set_motor_direction(DIRN_STOP);
		lastFloor = elev_get_floor_sensor_signal();
		elev_set_floor_indicator(lastFloor);
		printf("LastFloor %d\n", lastFloor);
	}
	*/
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
				queueAdd(arrayDown, i-1);
				elev_set_button_lamp(BUTTON_CALL_DOWN, i, 1);
			}
		}
		
		if (elev_get_button_signal(BUTTON_COMMAND, i) == 1) {
			elev_set_button_lamp(BUTTON_COMMAND, i, 1);
			if (i != 0){
				queueAdd(arrayDown, i-1);

			}
			if (i != 3){
				queueAdd(arrayUp, i);
			}
		}
		queuePrint();
		
	}
}

//Setter variabelen direction avhengig av hvor heis er og hvilke knapper som er trykket.
int fsmSetDirection() {
	if (elev_get_floor_sensor_signal() != -1){
		int Floor = elev_get_floor_sensor_signal();
		printf("Floor %d\n", Floor);
		
		switch(Floor){
			case 0:
				direction = 1;
				printf("case 0 %d\n", direction);
				return direction;
	
			case 1:	

				if (arrayDown[0]) {
					direction = -1;
					printf("case 1 %d\n", direction);
					return direction;
				}
				if (arrayUp[1] || arrayUp[2] || arrayDown[2]) {
					direction = 1;
					printf("case 1 %d\n", direction);
					return direction;
				}	

			case 2:
				if (arrayDown[0] || arrayUp[1] || arrayUp[0]) {
					direction = -1;
					printf("case 2 %d\n", direction);
					return direction;
				}
				if (arrayDown[2]) {
					direction = 1;
					printf("case 2 %d\n", direction);
					return direction;
				}
	
			case 3: {
				direction = -1;
				printf("case 3 %d\n", direction);
				return direction;
			}
			default:
				if(nextFloor == -1){
					direction = 0;
				}
				direction = 0;
				printf("Direction %d\n", direction);
		}
	}
}

//Stop state-machine:
/*
int fsmStop(){
	elev_set_stop_lamp(1);
	queueClear(arrayUp[]);
	queueClear(arrayDown[]);
	return;
}
*/

/*
void fsmRun(){
	//printf("LastFloor %d\n", lastFloor);
	//direction = fsmSetDirection();
	//printf("Direction %d\n", direction);
	nextFloor = queueGetNextFloor(arrayDown, arrayUp, fsmSetDirection());
	//printf("NextFloor %d\n", nextFloor);

	while (!(queueIsEmpty(arrayUp)) || !(queueIsEmpty(arrayDown))) {
		if (fsmSetDirection() == 1) {
			printf("Skal kjoere oppover\n");
			elev_set_motor_direction(DIRN_UP);
			queuePrint();
			//printf("LastFloor %d\n", lastFloor);
			//printf("NextFloor %d\n", nextFloor);
			//printf("Etasje %d\n", elev_get_floor_sensor_signal());
			//if(elev_get_floor_sensor_signal() != -1){
			//	lastFloor = nextFloor;
			//}
			if (lastFloor == nextFloor){
			//if (elev_get_floor_sensor_signal() == nextFloor) {
				printf("Yes, kom endelig inn i up-loop\n");
				elev_set_floor_indicator(lastFloor);
				elev_set_motor_direction(DIRN_STOP);
				queuePopFloor(arrayUp, nextFloor - 1);
				queuePopFloor(arrayDown, nextFloor);
				elev_set_button_lamp(BUTTON_COMMAND,nextFloor,0);
				elev_set_button_lamp(BUTTON_CALL_DOWN,nextFloor,0);
				elev_set_button_lamp(BUTTON_CALL_UP, nextFloor,0);
				
				lastFloor = nextFloor;
				//direction = fsmSetDirection();
				nextFloor = queueGetNextFloor(arrayDown, arrayUp, fsmSetDirection());
				//printf("LastFloor %d\n", lastFloor);
				//printf("NextFloor %d\n", nextFloor);
			}
			break;
		}
		
		if (fsmSetDirection() == -1) {
			printf("Skal kjoere nedover\n");
			elev_set_motor_direction(DIRN_DOWN);
			queuePrint();
			//printf("LastFloor %d\n", lastFloor);
			//printf("NextFloor %d\n", nextFloor);
			//printf("Etasje %d\n", elev_get_floor_sensor_signal());
			//if(elev_get_floor_sensor_signal() != -1){
			//	lastFloor = nextFloor;
			//}
			if(lastFloor == nextFloor){
			//if (elev_get_floor_sensor_signal() == nextFloor) {
				printf("Yes, kom endelig inn i down-loop\n");
				elev_set_floor_indicator(lastFloor);
				elev_set_motor_direction(DIRN_STOP);
				queuePopFloor(arrayUp, nextFloor);
				queuePopFloor(arrayDown, nextFloor - 1);
				elev_set_button_lamp(BUTTON_COMMAND,nextFloor,0);
				elev_set_button_lamp(BUTTON_CALL_DOWN,nextFloor,0);
				elev_set_button_lamp(BUTTON_CALL_UP, nextFloor,0);
				
				lastFloor = nextFloor;
				//direction = fsmSetDirection();
				nextFloor = queueGetNextFloor(arrayDown, arrayUp, fsmSetDirection());
				//printf("LastFloor %d\n", lastFloor);
				//printf("NextFloor %d\n", nextFloor);
			}
			break;
		}
		
		if (fsmSetDirection() == 0) {
			break;
		}
	}
	return;
}
*/

void fsmRun(){
	fsmSetDirection();
	nextFloor = queueGetNextFloor(arrayDown, arrayUp, lastFloor);
	printf("LastFloor %d\n", lastFloor);
	printf("NextFloor %d\n", nextFloor);
	if(!(queueIsEmpty(arrayDown) || !(queueIsEmpty(arrayUp)))) {

		if(direction == 1) {
			printf("Retningen blir satt oppover \n");
			elev_set_motor_direction(DIRN_UP);
			
		}
		

		if(direction == -1) {
			printf("Retningen blir satt nedover \n");
			elev_set_motor_direction(DIRN_DOWN);
			
		}
		
		
	}
	if (nextFloor == elev_get_floor_sensor_signal()) {
		elev_set_motor_direction(DIRN_STOP);
		queuePopFloor(nextFloor);
		lastFloor = nextFloor;
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
