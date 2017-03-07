#include "elev.h"
#include "fsm.h"
#include <stdio.h>



int main() {
    // Initialize hardware
    

    printf("Press STOP button to stop elevator and exit program.\n");

    //int UP_array[3] = 0;
    //int DOWN_array[3] = 0;

    fsmStart();

    while(1){
        

    }
    









    /*
    while(1){
        switch(elev_state) {
            case IDLE:
                printf("IDLE ");
                elev_state = DOWN;
                if(elev_get_stop_signal() == 1) {
                    elev_set_motor_direction(DIRN_STOP);
                    elev_state = STOPP;
                }
                break;
                
            case UP:
                printf("UP ");
                elev_set_motor_direction(DIRN_UP);
                if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
                    elev_set_motor_direction(DIRN_DOWN);
                    elev_state = DOWN;
                }

                if(elev_get_stop_signal() == 1) {
                    elev_set_motor_direction(DIRN_STOP);
                    elev_state = STOPP;
                }
                break;

            case DOWN:
                printf("DOWN ");
                elev_set_motor_direction(DIRN_DOWN);
                if (elev_get_floor_sensor_signal() == 0) {
                    elev_set_motor_direction(DIRN_UP);
                    elev_state = UP;
                }

                if(elev_get_stop_signal() == 1) {
                    elev_set_motor_direction(DIRN_STOP);
                    elev_state = STOPP;
                }
                break;

            case STOPP:
                printf("STOPP ");
                elev_set_stop_lamp(1); //Slett bestillinger, ignorer bestillinger, lys stoppknapp, etasjesensonr høy, dørene åpen til stoppknappen slippes.
                elev_set_motor_direction(DIRN_STOP);    
                //queueClear(UP_array);             //Slett bestillinger i kø
                //queueClear(DOWN_array);
                while ((elev_get_floor_sensor_signal() != -1) && elev_get_stop_signal()){
                    io_set_bit(LIGHT_DOOR_OPEN);
                }
                io_clear_bit(LIGHT_DOOR_OPEN);
                elev_set_stop_lamp(0);
                
                elev_state = IDLE;
                break;



        }

    }
    */

    return 0;
}
