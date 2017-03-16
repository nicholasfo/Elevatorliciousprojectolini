#include "elev.h"
#include "fsm.h"
#include "timer.h"
#include <stdio.h>



int main() {
	fsmStart();									//initialization, goes to a floor and waits for an order.

    while(1){
		if (elev_get_stop_signal() == 1) {
			fsmStop();							//Deletes orderes and sets stop-light.
		}
		fsmTakeOrders();						//Orginizes orderes and put then in queue.
		
		fsmRun();
/*
		if(moving == 0 && timer_on == 0){
			//fsmRun();
		}
		etasje = elev_get_floor_sensor_signal();
		if(etasje != -1){
			fsmStopAtFloor(etasje);
		}
        */

    }

    return 0;
}
