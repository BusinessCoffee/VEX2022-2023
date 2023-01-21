using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor roller;
extern motor launcher01;
extern motor launcher02;
extern motor launcher_single;
extern motor left_front;
extern motor left_rear;
extern motor right_front;
extern motor right_rear;
extern digital_out end_game_launcher;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );