//Tilstandsmaskin for denne supre haisen som er kodet av to tullinger som liker sushi og sake bedre enn å ta heis.
#include "channels.h"




//Start state-machine:
int fsmStart(){


};

//Stop state-machine:
int fsmStopp(state ){


};

//Is state-machine at ordered floor:
int fsmCorrectFloor(){


};

//Checks if there still is orders in queue:
int fsmStillOrdersInQueue(){


};

//Stops the elevator when arraived at ordered floor:
int fsmStopAtFloor(){


};

//Checks if stop-button is pressed:
int fsmStopPressed(){
	if(STOP == 1) {
		return 1;
	}
	else {
		return 0;
	}

};

//Checks if stop-button is released:
int fsmStopReleased(){


};