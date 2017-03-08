//Tilstandsmaskin for denne supre haisen som er kodet av to tullinger som liker sushi og sake bedre enn å ta heis.
#include "channels.h"
#include "koesystem.h"
#include "elev.h"
#include <stdio.h>

int arrayUp[3] = 0;
int arrayDown[3] = 0;

int direction = -2;			// -1 = ned, 0 = stop, 1 = opp
int lastFloor = -1;			// 0 = 1.etg, 1 = 2.etg, 2 = 3.etg, 3 = 4.etg
int nextFloor = -1;			//

//Start state-machine:
void fsmStart(){
	elev_init();
	if(elev_get_floor_sensor_signal() == -1) {
		elev_set_motor_direction(DIRN_DOWN);
		while(1){
			if(elev_get_floor_sensor_signal() != -1) {
				elev_set_motor_direction(DIRN_STOP);
				lastFloor = elev_get_floor_sensor_signal();
				
				break;
			}
		}
	}
}

void fsmTakeOrders() {
	for (int i = 0, i < 4, i++) {							
		if (i != 3) {
			if (elev_get_button_signal(BUTTON_CALL_UP, i) == 1) {
				queueAddUp(elev_get_button_signal(BUTTON_CALL_UP, i), i);
			}
		}
		if (i != 0) {
			if (elev_get_button_signal(BUTTON_CALL_DOWN, i) == 1) {
				queueAddDown(elev_get_button_signal(BUTTON_CALL_DOWN, i), i);
			}
		}
		if (elev_get_button_signal(BUTTON_COMMAND, i) == 1) {
			queueAddUp(elev_get_button_signal(BUTTON_COMMAND, i), i);
			queueAddDown(elev_get_button_signal(BUTTON_COMMAND, i), i);
		}
	}
}

//Stop state-machine:
int fsmStopp(){
	elev_set_stop_lamp(1);
	queueClear(arrayUp[]);
	queueClear(arrayDown[]);
	return;
}

void fsmRun() {
	direction = fsmSetDirection();
	nextFloor = queueGetNext(arrayDown[], arrayUp[], direction);

	while (!(queueIsEmpty(arrayUp[])) && !(queueIsEmpty(arrayDown[]))) {
		if (direction == 1) {
			printf("Skal kjoere oppover\n");
			elev_set_motor_direction(DIRN_UP);
			if (elev_get_floor_sensor_signal() == nextFloor) {
				elev_set_motor_direction(DIRN_STOP);
				queuePopFloor(arrayUp[], nextFloor);
				lastFloor = nextFloor;
				direction = fsmSetDirection();
				nextFloor = queueGetNext(arrayDown[], arrayUp[], direction);
			}
		}
		if (direction == -1) {
			printf("Skal kjoere nedover\n");
			elev_set_motor_direction(DIRN_DOWN);
			if (elev_get_floor_sensor_signal() == nextFloor) {
				elev_set_motor_direction(DIRN_STOP);
				queuePopFloor(arrayDown[], nextFloor);
				lastFloor = nextFloor;
				direction = fsmSetDirection;
				nextFloor = queueGetNext(arrayDown[], arrayUp[], direction);
			}
		}
		if (direction == 0) {
			return;
		}
	}
	return;
}

//Setter variabelen direction avhengig av hvor heis er og hvilke knapper som er trykket.
int fsmSetDirection() {
	if (lastFloor == 0) {
		direction = 1;
		return direction;
	}
	if (lastFloor == 1) {
		if (arrayDown[0]) {
			direction = -1;
			return direction;
		}
		if (arrayUp[1] || arrayUp[2]) {
			direction = 1;
			return direction;
		}
	}
	if (lastFloor == 2) {
		if (arrayDown[0] || arrayDown[1]) {
			direction = -1;
			return direction;
		}
		if (arrayUp[2]) {
			direction = 1;
			return direction;
		}
	}
	if (lastFloor == 3) {
		direction = -1;
		return direction;
	}
	else {
		return -2;
	}
}

int fsmCorrectFloor(int lastFloor, elev_motor_direction_t motordirection) {
	switch (motordirection) {

	case DIRN_STOP:
		for (int i = 0; i < N_FLOORS; i++) {
			if (arrayUp[i]) {
				return i;
			}

			if (arrayDown[i]) {
				return i;
			}
		}

		return lastFloor;

	case DIRN_DOWN:
		for (int i = lastFloor; i >= 0; i--) {
			if (arrayDown[i]) {
				return i;
			}
		}

		for (int i = 0; i < N_FLOORS; i++) {
			if (arrayUp[i] || arrayDown[i]) {
				return i;
			}
		}

	case DIRN_UP:
		for (int i = lastFloor; i < N_FLOORS; i++) {
			if (arrayUp[i]) {
				return i;
			}
		}

		for (int i = N_FLOORS - 1; i >= 0; i--) {
			if (arrayDown[i] || arrayUp[i]) {
				return i;
			}
		}

	default:
		return lastFloor;

	}

}

void fsmStopAtFloor(int floor) {

	//Heisen oppdager at den kommer til en etasje
	if (lastFloor != floor && floor != -1) {
		lastFloor = floor;
		elev_set_floor_indicator(lastFloor);

		//Funksjonen sjekker om etasjen den nå har kommet til er den samme som correctFloor returnerer.  
		if (fsmCorrectFloor(lastFloor, direction) == lastFloor) {
			elev_set_motor_direction(DIRN_STOP);
			direction = DIRN_STOP;
			queuePopFloor(arrayUp[], lastFloor);
			queuePopFloor(arrayDown[], lastFloor);
			timerStart();
			while (timeIsUp() == 0) {

				elev_set_door_open_lamp(1);		//Funker dette, eller må den settes lav igjen etter while er ferdig? idk

			}
			elev_set_door_open_lamp(0);
		}

		direction = queueGetNext(arrayUp, arrayDown, direction);
		motordirection = direction;
		elev_set_motor_direction(direction);

	}