#include <stdio.h>

int arrayDown[3] = {0,0,0}; //
int arrayUp[3] = {0,0,0};


//Adds elements to the arrays:
void queueAdd(int array[], int floor){				//[Opp i 1., Opp i 2., Opp i 3.]
	array[floor] = 1;
}

//Checks if the queue is empty:
int queueIsEmpty(int array[]){
	if((array[0] == 0) && (array [1] == 0) && (array [2] == 0)) {
		return 1;
	}
	else {
		return 0;
	}

}

//Removes the last arrived floor from array:

void queuePopFloor(int floor){
	if (floor != 0){
		arrayDown[3-floor] = 0;

	}
	if (floor != 3){
		arrayUp[floor] = 0;

	}

}

/*
void queuePopFloor(int array[], int floor){
	if (floor != 0){
		arrayDown[floor-1] = 0;

	}
	if (floor != 3){
		arrayUp[floor] = 0;

	}

}
*/

//Returns the next destination floor from array:
int queueGetNextFloor(int direction ,int floor){
	int array; // 1 = UP, -1 = DOWN
	int i = 0;
	if ((queueIsEmpty(arrayDown)) && (queueIsEmpty(arrayUp))) {
		return floor;
	}	

	if((direction == 1 && floor != 3) || (direction == -1 && floor == 0)){
			array = 1;
		}
	else {
		array = -1;
	}

	if(array == 1){
		i = floor;
	}
	if(array == -1){
		i = 3-floor;
	}

	while(1){
		if(array == 1){
			if(arrayUp[i]){
				return i;
			}

		}
		if(array == -1){
			if(arrayDown[i]){
				return 3-i;
			}

		}
		if(i == 2){
			array = -array;
			i = -1;
		}
		i++;
	}



		/*
		switch(floor){
			case 0:
				if(arrayDown[0] || arrayUp[1]){
					return 1;
				}
				if(arrayDown[1] || arrayUp[2]){
					return 2;
				}
				if(arrayDown[2]){
					return 3;
				}
			case 1:
				if (arrayUp[0]){
					return 0;
				}
				if (arrayDown[1] || arrayUp[2]){
					return 2;
				}
				if(arrayDown[2]){
					return 3;
				}
			case 2:
				if(arrayUp[0]){
					return 0;
				}
				if(arrayDown[0] || arrayUp[1]){
					return 1;
				}
				if(arrayDown[2]){
					return 3;
				}
			case 3:
				if(arrayUp[0]){
					return 0;
				}
				if(arrayDown[0] || arrayUp[1]){
					return 1;
				}
				if(arrayDown[1] || arrayUp[2]){
					return 2;
				}
			default:
				return floor;
		
		}


		
		//kan benytte switch (direction)?
		if (direction == -1) {
			if (arraydown[2]) {
				next = 3;
				return next;
			}
			if (arraydown[1]) {
				next = 2;
				return next;
			}
			if (arraydown[0]) {
				next = 1;
				return next;
			}
		}
		if (direction == 1) {
			if (arrayup[0]) {
				next = 0;
				return next;
			}
			if (arrayup[1]) {
				next = 1;
				return next;
			}
			if (arrayup[2]) {
				next = 2;
				return next;
			}

		}
		*/
	

}

//Clears floor-array when stop-button is pressed:
void queueClear(){
	for(int i=0; i<3; i++){
		arrayUp[i] = 0;
		arrayDown[i] = 0;
	}

}


void queuePrint(){
	printf("Up - array %d,%d,%d  ", arrayUp[0], arrayUp[1], arrayUp[2]);
	printf("Down-array %d,%d,%d\n", arrayDown[2], arrayDown[1], arrayDown[0]);
	return;

}

int queueGetNextDir(int direction, int floor){
	int nextfloor = queueGetNextFloor(direction, floor);
	if(nextfloor > floor){
		return 1;
	}
	if(nextfloor < floor){
		return -1;
	}
	return 0;
	
}
