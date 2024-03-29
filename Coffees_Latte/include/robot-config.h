using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor portal;
extern motor shoot01;
extern motor shoot02;
extern motor pharynx;
extern motor left_front;
extern motor left_rear;
extern motor right_front;
extern motor right_rear;
extern digital_out railgun;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );