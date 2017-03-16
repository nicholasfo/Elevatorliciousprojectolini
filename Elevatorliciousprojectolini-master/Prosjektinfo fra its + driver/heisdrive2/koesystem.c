#include <stdio.h>

int arrayDown[3] = {0,0,0}; //
int arrayUp[3] = {0,0,0};


//Add elements to arrays:
void queueAdd(int array[], int floor){	
	array[floor] = 1;
}

//Checks if queue is empty:
int queueIsEmpty(int array[]){
	if((array[0] == 0) && (array [1] == 0) && (array [2] == 0)) {
		return 1;
	}
	else {
		return 0;
	}

}

//Removes floor:
void queuePopFloor(int floor){
	if (floor != 0){
		arrayDown[3-floor] = 0;

	}
	if (floor != 3){
		arrayUp[floor] = 0;

	}

}

//Returns the next destination floor:
int queueGetNextFloor(int direction ,int floor){
	int array; // 1 = arrayUp, -1 = arrayDown
	int i = 0;
	if ((queueIsEmpty(arrayDown)) && (queueIsEmpty(arrayUp))) {
		return floor;
	}	

	if((direction == 1 && floor != 3) || (direction == -1 && floor == 0)){		//Sets array to a value, which is used to choose between te two order-arrays.
			array = 1;		//Chooses arrayUp
		}
	else {
		array = -1;			//Chooses arrayDown
	}

	if(array == 1){			//i is used to iterate through the arrays, has differen values based on Up- or Down-array
		i = floor;			
	}
	if(array == -1){
		i = 3-floor;
	}

	while(1){
		if(array == 1){
			if(arrayUp[i]){	//returns the position in the array if it is 1.
				return i;
			}

		}
		if(array == -1){
			if(arrayDown[i]){
				return 3-i;
			}

		}
		if(i == 2){
			array = -array;	//if it has reached the end of the current array, switches to the other array
			i = -1;
		}
		i++;
	}
}

//Clears both-arrays:
void queueClear(){
	for(int i=0; i<3; i++){
		arrayUp[i] = 0;
		arrayDown[i] = 0;
	}

}

//Printer ut hva køen inneholder:
void queuePrint(){
	printf("Up - array %d,%d,%d  ", arrayUp[0], arrayUp[1], arrayUp[2]);
	printf("Down-array %d,%d,%d\n", arrayDown[2], arrayDown[1], arrayDown[0]);
	return;

}

//Returns next direction:
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
