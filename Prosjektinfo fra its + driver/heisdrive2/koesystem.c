

//Adds elements to the arrays:
void queueAddUp(int array[3], int floor){				//[Opp i 1., Opp i 2., Opp i 3.]
	array[floor] = 1;
}

void queueAddDown(int array[3], int floor) {			//[Ned i 2., Ned i 3., Ned i 4.]
	array[floor] = 1;
}


//Checks if the queue is empty:
int queueIsEmpty(int array[3]){
	if((array[0] && array [1] && array [2]) == 0) {
		return 1;
	}
	else {
		return 0;
	}

}

//Removes the last arrived floor from array:
void queuePopFloor(int array[3], int floor){
	array[floor] = 0;

}

//Returns the next destination floor from array:
int queueGetNext(int array[3]){


}

//Clears floor-array when stop-button is pressed:
void queueClear(int array[3]){
	int i;
	for(i=0; i<2; i++){
		array[i] = 0;
	}

}