//headerfil for fsm.c
extern int direction;
extern int lastFloor;

//Set elevator in a state
//int fsmSetState(state state);

//Start state-machine:
void fsmStart();

//Receive orders
void fsmTakeOrders();

//Stop state-machine:
void fsmStop();

//Run statemachine
void fsmRun();

//Is state-machine at ordered floor:
//int fsmCorrectFloor(int lastFloor, elev_motor_direction_t motordirection);

//Stops the elevator when arraived at ordered floor:
void fsmStopAtFloor();