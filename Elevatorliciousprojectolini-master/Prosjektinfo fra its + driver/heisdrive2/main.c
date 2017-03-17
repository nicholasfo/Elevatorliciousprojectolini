#include "elev.h"
#include "fsm.h"
#include "timer.h"
#include <stdio.h>



int main() {
	fsmInit();									//initialization, goes down to a floor and waits for an order.

    while(1){
		if (elev_get_stop_signal() == 1) {
			fsmStop();							//Deletes orderes and runs stop-routines.
		}
		fsmTakeOrders();						//Orginizes orderes and put then in queue.
		
		fsmRun();								//Gets next direction, next floor and starts motor.

		fsmStopAtFloor();						//Checks if arrived at correct floor and runs correct-floor-routines.

    }

    return 0;
}
