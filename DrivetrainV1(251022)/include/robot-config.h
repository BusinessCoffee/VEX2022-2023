using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor BLWheel;
extern motor BRWheel;
extern motor FRWheel;
extern motor FLWheel;
extern motor Intake;
extern motor Transit;
extern motor Launcher;
extern motor String;
extern digital_out LPneumatic;
extern digital_out RPneumatic;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );