

//Adds elements to the arrays:
void queueAdd(int array[], int floor){				//[Opp i 1., Opp i 2., Opp i 3.]
	array[floor] = 1;
}

//Checks if the queue is empty:
int queueIsEmpty(int array[]){
	if((array[0] && array [1] && array [2]) == 0) {
		return 1;
	}
	else {
		return 0;
	}

}

//Removes the last arrived floor from array:
void queuePopFloor(int array[], int floor){
	array[floor] = 0;

}

//Returns the next destination floor from array:
int queueGetNext(int arraydown[], int arrayup[], int direction){
	int next = -2;
	if (!(queueIsEmpty(arraydown)) && !(queueIsEmpty(arrayup))) {
		//kan benytte switch (direction)?
		if (direction == -1) {
			if (arraydown[2]) {
				next = 2;
				return next;
			}
			if (arraydown[1]) {
				next = 1;
				return next;
			}
			if (arraydown[0]) {
				next = 0;
				return next;
			}
		}
		if (direction == 1) {
			if (arrayup[0]) {
				next = 1;
				return next;
			}
			if (arrayup[1]) {
				next = 2;
				return next;
			}
			if (arrayup[2]) {
				next = 3;
				return next;
			}

		}
	}
	return next;
}

//Clears floor-array when stop-button is pressed:
void queueClear(int array[3]){
	int i;
	for(i=0; i<3; i++){
		array[i] = 0;
	}

}