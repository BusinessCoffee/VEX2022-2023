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
// roller               motor         1               
// launcher01           motor         2               
// launcher02           motor         3               
// launcher_single      motor         4               
// left_front           motor         5               
// left_rear            motor         6               
// right_front          motor         7               
// right_rear           motor         8               
// end_game_launcher    digital_out   A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "string"
#include "iostream"

using namespace vex;
using namespace std;

competition Competition;

/*Config*/
double default_speed = 95; //  percentage

void pre_auton(void) {
  /*Drivetrain*/
  motor_group(left_front, left_rear, right_front, right_rear).setVelocity(default_speed, pct);
  motor_group(left_front, left_rear, right_front, right_rear).setStopping(coast);
  
  /*Other Motors*/
  motor_group(launcher01, launcher02, launcher_single).setVelocity(100, pct);
  motor_group(launcher01, launcher02, launcher_single).setStopping(brake);

  roller.setVelocity(default_speed, pct);
  roller.setStopping(brake);

  vexcodeInit();
}

/*-----------------------------------------*/

/*Drive*/
void drive (char dir, float dis){
  switch (dir){
    case 'w':
      motor_group(left_front, left_rear, right_front, right_rear).spinFor(fwd, dis, rev, false);
      break;
    case 's':
      motor_group(left_front, left_rear, right_front, right_rear).spinFor(reverse, dis, rev, false);
      break;
    case 'a':
      motor_group(left_front, right_rear).spinFor(fwd, dis, rev, false);
      motor_group(left_rear, right_front).spinFor(reverse, dis, rev, false);
      break;
    case 'd':
      motor_group(left_front, right_rear).spinFor(reverse, dis, rev, false);
      motor_group(left_rear, right_front).spinFor(fwd, dis, rev, false);
      break;
    case 'q':
      motor_group(left_front, left_rear).spinFor(reverse, dis, rev, false);
      motor_group(right_front, right_rear).spinFor(fwd, dis, rev, false);
      break;  
    case 'e':
      motor_group(left_front, left_rear).spinFor(fwd, dis, rev, false);
      motor_group(right_front, right_rear).spinFor(reverse, dis, rev, false);
      break;  
    default:
      break;
  }
}

void shoot(float dis){
  motor_group(launcher01, launcher02, launcher_single).spinFor(fwd, dis, rev, false);
}

void rol(double dis){
  roller.spinFor(fwd, dis, rev, false);
}

/*-----------------------------------------*/

void rollerTurn(){
  drive('s', 2);
  drive('e', 2);  //  Rotate 90 degrees
  drive('d', 2);
  drive('w', 2);
}

void autonomous(void) {
  float rollerDis = .25;

  drive('w', 2);
  rol(rollerDis); //  First roller
  rollerTurn();
  rol(rollerDis); //  Second roller
  drive('s', 2);
  drive('e', 3);
  drive('w', 15);
  drive('q', 1);
  drive('w', 2);
  rol(rollerDis); //  Third roller
  rollerTurn();
  rol(rollerDis); //  Final roller
}

/*-----------------------------------------*/

void usercontrol(void) {
  while (1) {
    
    /*Drive*/
    int _fwd = Controller1.Axis3.position(pct);
    int side = Controller1.Axis4.position(pct);
    int rot = Controller1.Axis1.position(pct);

    left_rear.spin(vex::fwd, _fwd-side+rot, pct);
    left_front.spin(vex::fwd, _fwd+side+rot, pct);
    right_rear.spin(vex::fwd, _fwd+side-rot, pct);
    right_front.spin(vex::fwd, _fwd-side-rot, pct);

/*-----------------------------------------*/

    /*Roller*/
    if (Controller1.ButtonL1.pressing() || Controller1.ButtonL2.pressing()){
      if (Controller1.ButtonL1.pressing()){
        roller.spin(fwd, default_speed, pct);
      }
      else if(Controller1.ButtonL2.pressing()){
        roller.spin(reverse, default_speed, pct);
      }
    }
    else{
      roller.stop();
    }

    /*Launcher*/
    if (Controller1.ButtonR1.pressing()){
      shoot(25);
    }
    else{
      motor_group(launcher01, launcher02, launcher_single).stop();
    }

    /*End Game*/
    if (Controller1.ButtonA.pressing()){
      end_game_launcher.set(true);
    }
    else{
      end_game_launcher.set(false);
    }

/*-----------------------------------------*/

    wait(20, msec);

  }
}
int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}
