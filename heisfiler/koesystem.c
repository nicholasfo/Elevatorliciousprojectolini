

#include "koesystem.h"
#include "elev.h"

typedef struct {
		int UpDir[N_FLOORS];
		int DownDir[N_FLOORS];
		int NoDir[N_FLOORS];
} Queue_t;

static Queue_t queue;

void queue_initialize(){								//IInitialisererererer structen ved å iterere gjennom og sette alt til null.

	for (int i = 0; i < N_FLOORS; i++){
		
		queue.UpDir[i] = 0;
		queue.DownDir[i] = 0;
		queue.NoDir[i] = 0;

	}

}

void queue_add(int floor, elev_button_type_t button){

	switch(button){

		case BUTTON_CALL_UP:							//Hvis BUTTON_CALL_UP trykkes inn og destinasjonsetasje ikke allerede er satt høy --> sett høy.
			if (queue.UpDir[floor] == 0){
				
				queue.UpDir[floor] = 1;

			}

			break;

		case BUTTON_CALL_DOWN:
			if (queue.DownDir[floor] == 0){				//Samme system som BUTTON_CALL_UP 
				
				queue.DownDir[floor] = 1;

			}

			break;

		case BUTTON_COMMAND:

			if (queue.NoDir[floor] == 0){
				
				queue.NoDir[floor] = 1;
			}
			break;
	}


}

void queue_delete_all(){

	for (int i = 0; i < N_FLOORS; i++){
		queue.UpDir[i] = 0;
		queue.DownDir[i] = 0;
		queue.NoDir[i] = 0;
	}

}

void queue_pop(int floor){

	if (queue.UpDir[floor] == 1){
		
		queue.UpDir[floor] = 0;
	
	}

	if (queue.DownDir[floor] == 1){
		
		queue.DownDir[floor] = 0;
	
	}

	if (queue.NoDir[floor] == 1){
		
		queue.NoDir[floor] = 0;
	
	}

}


int queue_getNextFloor(int currentFloor, elev_motor_direction_t queueDirection){
	
	switch(queueDirection){
		
		case DIRN_STOP:
			for (int i = 0; i < N_FLOORS; i++){
				if (queue.UpDir[i]){
					return i;
				}

				if (queue.DownDir[i]){
					return i;
				}

				if (queue.NoDir[i]){
					return i;
				}
			}

			return currentFloor;

		case DIRN_DOWN:

			for (int i = currentFloor; i >= 0; i--){
				if (queue.DownDir[i] || queue.NoDir[i]){
					return i;
				}
			}

			for (int i = 0; i < N_FLOORS; i++){
				if (queue.UpDir[i] || queue.DownDir[i] || queue.NoDir[i]){
					return i;
				}
			}

		case DIRN_UP:

				for (int i = currentFloor; i < N_FLOORS; i++){
					if (queue.UpDir[i] || queue.NoDir[i]){
						return i;
				}	
			}

			for (int i = N_FLOORS - 1; i >= 0; i--){
            	if (queue.DownDir[i] || queue.UpDir[i] || queue.NoDir[i]){
                        return i;
               	}
            }

		default: 
			return currentFloor;
	}
}

elev_motor_direction_t queue_GetNextDirection(int currentFloor, elev_motor_direction_t queueDirection){
	int diff = currentFloor - queue_getNextFloor(currentFloor,queueDirection);
	if (diff > 0){
		return DIRN_DOWN;
	}

	if (diff < 0){
		return DIRN_UP;
	}

	else {
		return DIRN_STOP;
	}
}