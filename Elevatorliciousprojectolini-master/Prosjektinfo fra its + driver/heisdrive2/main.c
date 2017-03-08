#include "elev.h"
#include "fsm.h"
#include <stdio.h>



int main() {
	fsmStart();									//initialization, goes to a floor and waits for an order.

    while(1){
		if (elev_get_stop_signal() == 1) {
			//fsmStopp();							//Deletes orderes and sets stop-light.
		}
		fsmTakeOrders();						//Orginizes orderes and put then in queue.

        fsmRun();

    }

    return 0;
}
