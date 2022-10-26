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
// BLWheel              motor         20              
// BRWheel              motor         19              
// FRWheel              motor         18              
// FLWheel              motor         17              
// Intake               motor         16              
// Transit              motor         15              
// Launcher             motor         14              
// String               motor         13              
// LPneumatic           digital_out   A               
// RPneumatic           digital_out   B               
// ---- END VEXCODE CONFIGURED DEVICES ----

/*------------------------------------------------------------------------------------------*/

/*@@@@@@@@      @@@@    @@@    @@@@@@@@@@   @@@@@@
        @@    @@    @@   @@           @@    @@@@@@@@
        @@    @@    @@   @@          @@     @@    @@
  @@@@@@@@    @@    @@   @@        @@       @@    @@
        @@    @@    @@   @@       @@        @@    @@
        @@    @@    @@   @@       @@        @@@@@@@@
  @@@@@@@@      @@@@    @@@@      @@        @@@@@@
*/

/*------------------------------------------------------------------------------------------*/

#include "vex.h"
#include "string"

using namespace vex;
using namespace std;

// A global instance of competition
competition Competition;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
}
/*------------------------------------------------------------------------------------------*/

const int maxSpeed = 90; //Prevents port burns
int SharpTurn(string side)
{
    if (side == "right")
    {
    BLWheel.spin(fwd, maxSpeed, pct);
    BRWheel.spin(reverse, maxSpeed, pct);
    FLWheel.spin(fwd, maxSpeed, pct);
    FRWheel.spin(reverse, maxSpeed, pct);
  
    wait(1, seconds);

    BLWheel.stop();
    BRWheel.stop();
    FLWheel.stop();
    FRWheel.stop();
    }
    else
    {
    BLWheel.spin(reverse, maxSpeed, pct);
    BRWheel.spin(fwd, maxSpeed, pct);
    FLWheel.spin(reverse, maxSpeed, pct);
    FRWheel.spin(fwd, maxSpeed, pct);
  
    wait(1, seconds);

    BLWheel.stop();
    BRWheel.stop();
    FLWheel.stop();
    FRWheel.stop();
    }
    return (0);
}

int DriveForward(int length)
{
  BLWheel.spin(fwd, maxSpeed, pct);
  BRWheel.spin(fwd, maxSpeed, pct);
  FLWheel.spin(fwd, maxSpeed, pct);
  FRWheel.spin(fwd, maxSpeed, pct);
  
  wait(length, seconds);

  BLWheel.stop();
  BRWheel.stop();
  FLWheel.stop();
  FRWheel.stop();

  return(0);
}

/*------------------------------------------------------------------------------------------*/

void autonomous(void) {
  /*Config*/
  BLWheel.setStopping(brake);
  BRWheel.setStopping(brake);
  FRWheel.setStopping(brake);
  FLWheel.setStopping(brake);

  Intake.setStopping(hold);
  Transit.setStopping(hold);
  Launcher.setStopping(brake);
  String.setStopping(coast);

/*------------------------------------------------------------------------------------------*/

  BLWheel.setVelocity(maxSpeed, pct);
  BRWheel.setVelocity(maxSpeed, pct);
  FLWheel.setVelocity(maxSpeed, pct);
  FRWheel.setVelocity(maxSpeed, pct);

  Intake.setVelocity(maxSpeed, pct);
  Transit.setVelocity(maxSpeed, pct);
  Launcher.setVelocity(maxSpeed + 10, pct);
  String.setVelocity(maxSpeed + 10, pct);

  DriveForward(1);
  SharpTurn("right");
  SharpTurn("left");


/*------------------------------------------------------------------------------------------*/

}

/*------------------------------------------------------------------------------------------*/

void usercontrol(void) {
  while (1) {

  /*Drivetrain*/  
  int forward = Controller1.Axis3.position(percent);  // Reads the position of the joysticks to determine the speed the motors go
  int sideways = Controller1.Axis4.position(percent);
  int rot = Controller1.Axis1.position(percent);

  BLWheel.spin(vex::forward, forward/1.1 - sideways/1.1 + rot/1.1, vex::percent); // Drive control
  BRWheel.spin(vex::forward,  forward/1.1 + sideways/1.1 - rot/1.1, vex::percent);
  FLWheel.spin(vex::forward,  forward/1.1 + sideways/1.1 + rot/1.1, vex::percent);
  FRWheel.spin(vex::forward,   forward/1.1 - sideways/1.1 - rot/1.1, vex::percent);

  BLWheel.stop();
  BRWheel.stop();
  FLWheel.stop();
  FRWheel.stop();

/*------------------------------------------------------------------------------------------*/

  /*User Control*/
  while(Controller1.ButtonR2.pressing())  //  Intake : In
  {
    Intake.spin(fwd, maxSpeed, pct);
    Transit.spin(fwd, maxSpeed, pct);
  }
  while(Controller1.ButtonR1.pressing())  //  Intake : Out
  {
    Intake.spin(reverse, maxSpeed, pct);
    Transit.spin(fwd, maxSpeed, pct);
  }
////
  while(Controller1.ButtonL2.pressing())  //  Disc launcher : Shoot
  {
    Launcher.spin(fwd, maxSpeed + 10, pct);
  }
  while(Controller1.ButtonL1.pressing())  //  Disc launcher : In
  {
    Launcher.spin(reverse, maxSpeed + 10, pct);
  }
////
  while(Controller1.ButtonX.pressing()) //  Launches string
  {
    Launcher.spin(fwd, maxSpeed + 10, pct);
  }
  while(Controller1.ButtonX.pressing()) //  Tightens string
  {
    Launcher.spin(reverse, maxSpeed + 10, pct);
  }
////
  if(Controller1.ButtonUp.pressing()) //  Lifts disc launcher
  {
    LPneumatic.set(true);
    RPneumatic.set(true);
  }
  if(Controller1.ButtonDown.pressing()) //  Lowers disc launcher
  {
    LPneumatic.set(false);
    RPneumatic.set(false);
  }
/*------------------------------------------------------------------------------------------*/

  wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}