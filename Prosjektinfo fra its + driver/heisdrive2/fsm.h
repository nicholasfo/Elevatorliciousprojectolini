//headerfil for fsm.c

//Set elevator in a state
//int fsmSetState(state state);

//Start state-machine:
void fsmStart();

//Receive orders
void fsmTakeOrders();

//Stop state-machine:
int fsmStopp();

//Is state-machine at ordered floor:
int fsmCorrectFloor();

//Checks if there still is orders in queue:
int fsmStillOrdersInQueue();

//Stops the elevator when arraived at ordered floor:
int fsmStopAtFloor();