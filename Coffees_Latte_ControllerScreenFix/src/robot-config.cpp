#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor portal = motor(PORT16, ratio18_1, true);
motor shoot01 = motor(PORT14, ratio18_1, false);
motor shoot02 = motor(PORT12, ratio18_1, true);
motor pharynx = motor(PORT13, ratio18_1, false);
motor left_front = motor(PORT15, ratio18_1, true);
motor left_rear = motor(PORT17, ratio18_1, false);
motor right_front = motor(PORT20, ratio18_1, false);
motor right_rear = motor(PORT18, ratio18_1, true);
digital_out railgun = digital_out(Brain.ThreeWirePort.A);

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