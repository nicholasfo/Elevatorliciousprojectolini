

//Adds elements to the array for upward motion:
void queueAdd(int array[3], int floor){

};


//Checks if the queue is empty:
int queueIsEmpty(int array[3]){
	if(array[0] && array [1] && array [2] == 0) {
		return 1;
	}
	else {
		return 0;
	}

};

//Removes the last arrived floor from array:
void queuePop(int array[3]){


};

//Returns the next destination floor from array:
int queueGetNext(int array[3]){


};

//Clears floor-array when stop-button is pressed:
void queueClear(int array[3]){
	int i;
	for(i=0; i<2; i++){
		array[i] = 0;
	}

};