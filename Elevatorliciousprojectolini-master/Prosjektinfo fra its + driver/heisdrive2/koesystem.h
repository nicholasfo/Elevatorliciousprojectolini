//Headerfil for Koesystem.c

extern int arrayUp[3];
extern int arrayDown[3];

//Adds elements to the array for upward motion:
void queueAdd(int array[], int floor);

//Checks if the queue is empty:
int queueIsEmpty(int array[]);

//Removes the last arrived floor from array:
void queuePopFloor(int floor);

//Returns the next destination floor from array:
int queueGetNextFloor(int arraydown[], int arrayup[], int direction);

//Clears floor-array when stop-button is pressed:
void queueClear(int array[]);

//Prints current queue
void queuePrint();

//Gets next direction
int queueGetNextDir(int arraydown[], int arrayup[], int floor);

//get next direction
//floor and dir to queuePos
//queuePos to floor