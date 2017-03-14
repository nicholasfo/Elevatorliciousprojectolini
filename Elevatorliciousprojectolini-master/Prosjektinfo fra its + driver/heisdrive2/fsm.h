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
int fsmStop();

//Run statemachine
void fsmRun();

//Set Direction (variable and motor)
int fsmSetDirection();

//Is state-machine at ordered floor:
//int fsmCorrectFloor(int lastFloor, elev_motor_direction_t motordirection);

//Stops the elevator when arraived at ordered floor:
void fsmStopAtFloor(int floor);