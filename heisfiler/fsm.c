//Tilstandsmaskin for denne supre haisen som er kodet av to tullinger som liker sushi og sake bedre enn å ta heis.
#include "channels.h"
#include "koesystem.h"
#include "elev.h"
#include <stdio.h>


enum state {IDLE, UP, DOWN, STOPP};
enum state elev_state;

int arrayUp[3] = 0;
int arrayDown[3] = 0;

int direction = 0;			//0 = ned, 1 = opp
int lastFloor = -1;			//

//Start state-machine:
void fsmStart(){
	elev_init();
	if(elev_get_floor_sensor_signal() == -1) {
		elev_set_motor_direction(DIRN_DOWN);
		while(1){
			if(elev_get_floor_sensor_signal() != -1) {
				elev_set_motor_direction(DIRN_STOP);
				elev_state = IDLE;
				lastFloor = elev_get_floor_sensor_signal();
				break;
			}
		}
	}
}

void fsmTakeOrders() {
	for (int i = 0, i < 4, i++) {										//Legger til etasjer i up-koen om heisen staar under bestilt etasje
		if (i != 3) {
			if (elev_get_button_signal(BUTTON_CALL_UP, i) == 1) {}
			queueAddUp(elev_get_button_signal(BUTTON_CALL_UP, i), i);
		}
		if (i != 0) {
			if (elev_get_button_signal(BUTTON_CALL_DOWN, i) == 1) {}
			queueAddDown(elev_get_button_signal(BUTTON_CALL_DOWN, i), i);
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
	queueClear(arrayUp);
	queueClear(arrayDown);
	elev_state = STOPP;
}

/*
//Is state-machine at ordered floor:
int fsmCorrectFloor(){


}

//Checks if there still is orders in queue:
int fsmStillOrdersInQueue(){


}

//Stops the elevator when arraived at ordered floor:
int fsmStopAtFloor(){
	//Stopp heis
	//aapne doer
	//staa aapen i 3sek
	//

}
*/