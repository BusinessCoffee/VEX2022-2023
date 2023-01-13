#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor roller = motor(PORT15, ratio18_1, false);
motor launcher = motor(PORT14, ratio6_1, false);
motor intake = motor(PORT16, ratio18_1, false);
motor lFront = motor(PORT17, ratio36_1, false);
motor rFront = motor(PORT18, ratio36_1, true);
motor rRear = motor(PORT19, ratio36_1, true);
motor lRear = motor(PORT20, ratio36_1, false);

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