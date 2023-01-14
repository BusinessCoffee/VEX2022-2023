/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       coder                                                     */
/*    Created:      1/12/2023, 4:33:20 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// roller               motor         15              
// launcher             motor         14              
// intake               motor         16              
// lFront               motor         17              
// rFront               motor         18              
// rRear                motor         19              
// lRear                motor         20              
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "string.h"
#include "iostream"

using namespace std;
using namespace vex;

// A global instance of competition
competition Competition;

/*---------------------------------------*/
/*Config*/

//Velocity
int wheelPct = 100; //percentage
int digestPct = 90;

/*---------------------------------------*/

void pre_auton(void) {
  /*Config*/
  motor_group(lRear, rRear, lFront, rFront).setStopping(coast);
  motor_group(lRear, rRear, lFront, rFront).setVelocity(wheelPct, pct);
  intake.setStopping(brake);
  launcher.setStopping(brake);

  vexcodeInit();
}

/*---------------------------------------*/
/*Controller*/

void Shoot(){
  motor_group(launcher, intake).spin(fwd, digestPct, pct);
}

void Roller(string dir){
  if (dir == "in"){
    roller.spin(fwd, digestPct, pct);
    Controller1.rumble("...---");
  }else if (dir == "out"){
    roller.spin(reverse, digestPct, pct);
    Controller1.rumble("...---");
  }else{
    return;
  }
}

void Intake(string dir){
  if (dir == "in"){
    intake.spin(fwd, digestPct, pct);
    Controller1.rumble(".-");
  }else if (dir == "out"){
    intake.spin(reverse, digestPct, pct);
    Controller1.rumble(".-");
  }else{
    return;
  }
}

void Side(string dir, double revs){
  if (dir == "left"){
    /*Config*/
    lRear.setReversed(true);
    rRear.setReversed(false);
    lFront.setReversed(false);
    rFront.setReversed(true);
    
    /*Drive*/
    motor_group(lRear, rRear, lFront, rFront).spinFor(revs, rev);
  }else if (dir == "right"){
    /*Config*/
    lRear.setReversed(false);
    rRear.setReversed(true);
    lFront.setReversed(true);
    rFront.setReversed(false);

    /*Drive*/
    motor_group(lRear, rRear, lFront, rFront).spinFor(-revs, rev);
  }else{
    return;
  }
}

void Rotation(string dir, double revs){
  if (dir == "left"){
    /*Config*/
    lRear.setReversed(true);
    rRear.setReversed(true);
    lFront.setReversed(true);
    rFront.setReversed(true);
    
    /*Drive*/
    motor_group(lRear, rRear, lFront, rFront).spinFor(revs, rev);
  }else if (dir == "right"){
    /*Config*/
    lRear.setReversed(false);
    rRear.setReversed(false);
    lFront.setReversed(false);
    rFront.setReversed(false);

    /*Drive*/
    motor_group(lRear, rRear, lFront, rFront).spinFor(revs, rev);
  }else{
    return;
  }
}

void Forward(string dir, double revs){
  if (dir == "fwd"){
    motor_group(lRear, rRear, lFront, rFront).spinFor(revs, rev);
  }else if (dir == "rev"){
    motor_group(lRear, rRear, lFront, rFront).spinFor(-revs, rev);
  }else{
    return;
  }
}

/*---------------------------------------*/
void autonomous(void) {
  Forward("fwd", 3); // Gets in range
  Shoot();
  wait(2, seconds);
  Forward("rev", 3); // Backs up to roller
  Side("left", 3);
  Forward("rev", 5);
  Rotation("right", 5); // Rotates towards roller
  Forward("fwd", 3);
  Roller("in"); // Spins roller
  wait(2, seconds);
 
} 

void usercontrol(void) {
 
  while (1) {
    /*Drive*/
    int fwd = Controller1.Axis3.position(pct);
    int side = Controller1.Axis4.position(pct);
    int rot = Controller1.Axis1.position(pct);

    lRear.spin(vex::fwd, fwd - side + rot, pct);
    rRear.spin(vex::fwd, fwd + side - rot, pct);
    lFront.spin(vex::fwd, fwd + side + rot, pct);
    rFront.spin(vex::fwd, fwd - side - rot, pct);

    /*---------------------------------------*/
    /*Buttons*/

    if (Controller1.ButtonL1.pressing() || Controller1.ButtonL2.pressing()){
      if (Controller1.ButtonL1.pressing()){
        Intake("in");
      }else if (Controller1.ButtonL2.pressing()){
        Intake("out");
      }else{
        intake.stop();
      }
    }

    if (Controller1.ButtonR1.pressing() || Controller1.ButtonR2.pressing()){
      if (Controller1.ButtonR1.pressing()){
        Roller("in");
      }else if (Controller1.ButtonR2.pressing()){
        Roller("out");
      }else{
        roller.stop();
      }
    }

    if (Controller1.ButtonX.pressing()){
      Shoot();
    }else{
      launcher.stop();
    }

    wait(20, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
