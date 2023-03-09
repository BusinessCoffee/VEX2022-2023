/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// portal               motor         16
// shoot01              motor         14
// shoot02              motor         12
// pharynx              motor         13
// left_front           motor         15
// left_rear            motor         17
// right_front          motor         20
// right_rear           motor         18
// railgun              digital_out   A
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "iostream"
#include "string.h"
#include "vex.h"
using namespace vex;
using namespace std;
competition Competition;

int mode = 2;               // Shooting distance
float roller = .5;          // Revolutions
float default_speed = 100;  // Percentage
float shooting_speed = 100; // Percentage
float rightWheels = 85;
float charge_time = 2; // Seconds
bool debounce = true;

void pre_auton(void) {

  /*Motor Config*/
  //-----------------//Drivetrain
  motor_group(left_front, left_rear).setVelocity(50, pct);
  motor_group(right_front, right_rear).setVelocity(rightWheels, pct);
  motor_group(left_front, left_rear, right_front, right_rear)
      .setStopping(coast);

  //-----------------//Digestion System
  motor_group(shoot01, shoot02, pharynx).setVelocity(100, pct);
  portal.setVelocity(100, pct);
  motor_group(shoot01, shoot02).setStopping(brake);
  pharynx.setStopping(coast);

  vexcodeInit();
}

void cmd(char command, float dis, float delay) {
  switch (command) {
  case 'w': {
    motor_group(left_front, left_rear, right_front, right_rear)
        .spinFor(fwd, dis, rev, false); // Drive forward
    wait(delay, sec);
    break;
  }
  case 's': {
    motor_group(left_front, left_rear, right_front, right_rear)
        .spinFor(reverse, dis, rev, false); // Drive reverse
    wait(delay, sec);
    break;
  }
  case 'a': {
    motor_group(left_front, left_rear, right_front, right_rear)
        .spinFor(reverse, dis, rev, false); // Rotate left
    motor_group(right_front, right_rear).spinFor(fwd, dis, rev, false);
    wait(delay, sec);
    break;
  }
  case 'd': {
    motor_group(left_front, left_rear, right_front, right_rear)
        .spinFor(fwd, dis, rev, false); // Rotate right
    motor_group(right_front, right_rear).spinFor(reverse, dis, rev, false);
    wait(delay, sec);
    break;
  }
  case 'e': {
    portal.spinFor(roller, rev, false); //  Roller
    wait(delay, sec);
    break;
  }
  case 'q': {
    motor_group(shoot01, shoot02).spin(fwd, 100, pct); // Charge disc
    wait(delay, sec);
    motor_group(shoot01, shoot02).stop();
    break;
  }
  case 'x': {
    railgun.set(true); // Fires endgame
    wait(delay, sec);
    break;
  }
  case 'z': {
    motor_group(shoot01, shoot02, pharynx)
        .spin(fwd, 100, pct); // Shoot disc far
    wait(delay, sec);
    break;
  }
  default:
    break;
  }
}

/*Programming Control*/
//-----------------//Closest roller
void autonomous(void) {
 cmd('w', 1, 1); //1st roller
  cmd('e', roller, 1);
  cmd('s', 1, 1); //end

  cmd('z', -2, 1); //moves preload to pharynx

  cmd('a', 2, 2); //high goal shoot
  cmd('q', 0, charge_time);
  cmd ('z', 0, 1);  //end

  cmd('a', 1, 1);  //Push disc into low goal
  cmd('s', 5, 5); //end
}

void usercontrol(void) {
  while (1) {
    /*Motor Control*/
    //-----------------//Drivetrain
    int _fwd = Controller1.Axis3.position(pct);
    int side = Controller1.Axis4.position(pct);
    int rot = Controller1.Axis1.position(pct);

    left_rear.spin(vex::fwd, _fwd - side + rot, pct);
    left_front.spin(vex::fwd, _fwd + side + rot, pct);
    right_rear.spin(vex::fwd, _fwd + side - rot, pct);
    right_front.spin(vex::fwd, _fwd - side - rot, pct);

    //-----------------//Portal
    if (Controller1.ButtonL1.pressing() || Controller1.ButtonL2.pressing()) {
      if (Controller1.ButtonL1.pressing()) {
        portal.spin(fwd, default_speed, pct); // Intake
      } else if (Controller1.ButtonL2.pressing()) {
        portal.spin(reverse, default_speed, pct); // Vomit
      }
    } else {
      portal.stop();
    }

    //-----------------//Shoot
    if (Controller1.ButtonR1.pressing() || Controller1.ButtonR2.pressing()) {
      if (Controller1.ButtonR1.pressing()) {
        motor_group(shoot01, shoot02, pharynx)
            .spin(fwd, shooting_speed = 100, pct); // Shoot disc
      }
      if (Controller1.ButtonR2.pressing()) {
        motor_group(shoot01, shoot02, pharynx)
            .spin(reverse, shooting_speed = 100, pct); // Shoot disc
      }
    } else {
      motor_group(shoot01, shoot02, pharynx).stop();
    }
  }

  if (Controller1.ButtonUp.pressing() || Controller1.ButtonDown.pressing()) {
    if (Controller1.ButtonUp.pressing() && mode < 2 && debounce) {
      debounce = false;
      mode++;
      wait(.5, sec);
      debounce = true;
    } else if (Controller1.ButtonUp.pressing() && mode > 0 && debounce) {
      debounce = false;
      mode--;
      wait(.5, sec);
      debounce = true;
    }
  }

  //-----------------//Railgun
  if (Controller1.ButtonX.pressing()) {
    railgun.set(true);
  } else {
    railgun.set(false);
  }

  wait(20, msec);
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}