//Headerfil for Koesystem.c


//Adds elements to the array for upward motion:
void queueAdd(int array[], int floor);

//Checks if the queue is empty:
int queueIsEmpty(int array[]);

//Removes the last arrived floor from array:
void queuePopFloor(int array[], int floor);

//Returns the next destination floor from array:
int queueGetNext(int arraydown[], int arrayup[], int direction);

//Clears floor-array when stop-button is pressed:
void queueClear(int array[]);