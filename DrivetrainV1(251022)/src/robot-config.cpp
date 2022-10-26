#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor BLWheel = motor(PORT20, ratio36_1, false);
motor BRWheel = motor(PORT19, ratio36_1, true);
motor FRWheel = motor(PORT18, ratio36_1, true);
motor FLWheel = motor(PORT17, ratio36_1, false);
motor Intake = motor(PORT16, ratio18_1, false);
motor Transit = motor(PORT15, ratio18_1, false);
motor Launcher = motor(PORT14, ratio6_1, false);
motor String = motor(PORT13, ratio18_1, false);
digital_out LPneumatic = digital_out(Brain.ThreeWirePort.A);
digital_out RPneumatic = digital_out(Brain.ThreeWirePort.B);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}