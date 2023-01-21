#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor roller = motor(PORT1, ratio18_1, false);
motor launcher01 = motor(PORT2, ratio18_1, false);
motor launcher02 = motor(PORT3, ratio18_1, false);
motor launcher_single = motor(PORT4, ratio6_1, false);
motor left_front = motor(PORT5, ratio18_1, false);
motor left_rear = motor(PORT6, ratio18_1, false);
motor right_front = motor(PORT7, ratio18_1, true);
motor right_rear = motor(PORT8, ratio18_1, true);
digital_out end_game_launcher = digital_out(Brain.ThreeWirePort.A);

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