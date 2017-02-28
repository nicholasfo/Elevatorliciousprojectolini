#include "elev.h"
#include "fsm.h"
#include "channels.h"
#include "koesystem.h"
#include "io.h"
#include <stdio.h>



int main() {
    enum state {IDLE, UP, DOWN, STOPP};

    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    enum state elev_state = IDLE;


    printf("Press STOP button to stop elevator and exit program.\n");

    //elev_set_motor_direction(DIRN_UP);
    /*
    while (1) {
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }
*/
    //int array[3] = 0;
    //int DOWN_array[3] = 0;
    while(1){
        switch(elev_state) {
            case IDLE:
                while (elev_get_stop_signal() == 0) { //
                    
                    if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
                        elev_set_motor_direction(DIRN_DOWN);
                    }       
                    else if (elev_get_floor_sensor_signal() == 0) {
                        elev_set_motor_direction(DIRN_UP);
                    }

                }
                elev_set_motor_direction(DIRN_STOP);
                elev_state = STOPP;
                
                break;

            case UP:
                while (elev_get_stop_signal() == 0) { //


                }
                elev_set_motor_direction(DIRN_STOP);
                elev_state = STOPP;
                break;

            case DOWN:
                while (elev_get_stop_signal() == 0) { //


                }
                elev_set_motor_direction(DIRN_STOP);
                elev_state = STOPP;
                break;

            case STOPP:
                
                elev_set_stop_lamp(1); //Slett bestillinger, ignorer bestillinger, lys stoppknapp, etasjesensonr høy, dørene åpen til stoppknappen slippes.
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

    return 0;
}
