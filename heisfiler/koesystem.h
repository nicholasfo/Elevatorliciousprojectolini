//Headerfil for Koesystem.c


void queue_initialize();
void queue_add(int floor, elev_button_type_t button);
void queue_delete_all();
void queue_pop(int floor);
int queue_getNextFloor(int currentFloor, elev_motor_direction_t queueDirection);
elev_motor_direction_t queue_GetNextDirection(int currentFloor, elev_motor_direction_t queueDirection);