using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor roller;
extern motor launcher;
extern motor intake;
extern motor lFront;
extern motor rFront;
extern motor rRear;
extern motor lRear;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );