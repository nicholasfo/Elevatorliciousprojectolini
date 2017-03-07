//Tilstandsmaskin for denne supre haisen som er kodet av to tullinger som liker sushi og sake bedre enn å ta heis.
#include "channels.h"
#include "koesystem.h"
#include "elev.h"
#include <stdio.h>


enum state {IDLE, UP, DOWN, STOPP};
enum state elev_state;

//int fsmSetState(state state){
	
//	elev_state = state;
//	return 1;
//}

//Start state-machine:
void fsmStart(){
	elev_init();
	if(elev_get_floor_sensor_signal() == -1) {
		elev_set_motor_direction(DIRN_DOWN);
		while(1){
			if(elev_get_floor_sensor_signal() != -1) {
				elev_set_motor_direction(DIRN_STOP);
				elev_state = IDLE;
				printf("Heis nå satt i IDLE, venter på etasje-bestilling");
				break;
			}
		}
	}
}

/*//Stop state-machine:
int fsmStopp(){


} 

//Is state-machine at ordered floor:
int fsmCorrectFloor(){


}

//Checks if there still is orders in queue:
int fsmStillOrdersInQueue(){


}

//Stops the elevator when arraived at ordered floor:
int fsmStopAtFloor(){


}

//Checks if stop-button is pressed:				//Trenger vi denne?
int fsmStopPressed(){
	if(STOP == 1) {
		return 1;
	}
	else {
		return 0;
	}

}

//Checks if stop-button is released:
int fsmStopReleased(){
}
*/