//Headerfil for Koesystem.c


//Adds elements to the array for upward motion:
void queueAdd(int array[], int floor);

//Checks if the queue is empty:
int queueIsEmpty(int array[]);

//Removes the last arrived floor from array:
void queuePop(int array[], int floor);

//Returns the next destination floor from array:
int queueGetNext(int array[]);

//Clears floor-array when stop-button is pressed:
void queueClear(int array[]);