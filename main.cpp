// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// gyroo                inertial      20              
// intake               motor         15              
// catapult             motor         4               
// leftwing             digital_out   A               
// intakepistonb        digital_out   B               
// rightwing            digital_out   H               
// Controller1          controller                    
// RotationRight        rotation      21              
// RotationLeft         rotation      3               
// Opticall             optical       2               
// backleft             motor         17              
// middleleft           motor         16              
// frontleft            motor         12              
// backright            motor         18              
// middleright          motor         13              
// frontright           motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

// A global instance of competition
competition Competition;

// reform of old function
void forwardPIDD(int setpoint, int speed) {
  backleft.setPosition(0,degrees);
  float input = backleft.position(degrees);
  float power;
  float kP = 0.14 * (.01 * speed);
  // float kI = 0.0002;
  float kD = 0.5;
  
  float error = setpoint - input;
  // float integral = 0;
  float derivative = 0;
  float prevError = 0;
  
  float i = 1;
  while (abs(error) > i) {
    input = backleft.position(degrees);
    error = setpoint - input;
      float P = kP * error;
        // integral += error;
      // float I = kI * integral;
        derivative = error - prevError;
      float D = kD * derivative;
      power = P + D; 
  
    frontleft.spin(forward, power, pct);
    frontright.spin(forward, power, pct);
    middleleft.spin(forward, power, pct);
    middleright.spin(forward, power, pct);
    backleft.spin(forward, power, pct);
    backright.spin(forward, power, pct);
    prevError = error;
    wait(10, msec);
  }
    stopBase(); // Stop the drivetrain when the loop exits
}

void sensordisplays () {
  while (true) {
    Brain.Screen.printAt(15, 15, "%f", RotationRight.position(degrees));
    Brain.Screen.printAt(30, 30, "%f", RotationLeft.position(degrees));
    Brain.Screen.printAt(45, 45, "%f", gyroo.heading(degrees));
    Brain.Screen.printAt(60, 60, "Hue: %.2f", Opticall.hue());
    wait(10,msec);
    Brain.Screen.clearScreen();
  }
}

void clearmotors () {
  frontleft.resetPosition();
  frontright.resetPosition();
  backleft.resetPosition();
  backright.resetPosition();
  middleleft.resetPosition();
  middleright.resetPosition();
}

void clearall() {
  clearmotors();
  gyroo.resetHeading();
  RotationLeft.resetPosition();
  RotationRight.resetPosition();
}

void sWings(int setpoint) {
  leftwing.set(setpoint);
  rightwing.set(setpoint);
}

void pre() {
  clearall();
  // thread d(autofire);
  Controller1.Screen.setCursor(2,2);
  Controller1.Screen.print("Calibrating sensors...");
  gyroo.calibrate();
  wait(2.5, seconds);
  Controller1.Screen.setCursor(2,2);
  Controller1.Screen.print("      We're live!       ");
  wait(3, seconds);
  Controller1.Screen.setCursor(2,2);
  Controller1.Screen.print("      Go Luca !!!       ");
}

void offensive() {
  // start in the centre of the middle start tile w/ preload
  
  forwardPIDD(2000, 100);
  turnPID(-90, 90, -1);
    clearmotors();
  
  // score
  intake.spin(reverse, 100, pct);
  forwardPIDD(105, 100);
    wait(.01, sec);

  // collect triball a
  forwardPIDD(-300, 100);
  clearmotors();
  turnPID(-5, 90, -1);
    clearmotors();
  intake.spin(forward, 100, pct);
  forwardPIDD(350, 100);
    clearmotors();
    wait(.05, sec);

  // score
  forwardPIDD(-350, 100);
    clearmotors();
  turnPID(-90, 90, -1);
    clearmotors();
    intake.spin(reverse, 100, pct);
  forwardPIDD(500, 95);
    wait(.05, sec);
    clearmotors();

  // collect triball b
  forwardPIDD(-1050, 100);
    clearmotors();
  turnPID(0, 90, -1);
    clearmotors();
  intake.spin(forward, 100, pct);
  forwardPIDD(200, 100);
    wait(.1, sec);
    clearmotors();
  
  // score
  forwardPIDD(-200, 100);
    clearmotors();
  turnPID(-90, 90, -1);
    clearmotors();
  intake.spin(reverse, 100, pct);
  forwardPIDD(1050, 100);
    wait(.05, sec);
    intake.stop();
    clearmotors();

  // get triball c
  forwardPIDD(-200, 100); 
    clearmotors();
  turnPID(95, 85, -1);
    clearmotors();
    intake.spin(forward, 100, pct);
  forwardPIDD(1000, 100);
    clearmotors();
  
  // score
  // forwardPIDD(-1000, 95);
  //   clearmotors();
  // turnPID(0, 85, -1);
  //   clearmotors();
  // intake.spin(reverse, 100, pct);
  // forwardPIDD(200, 100);
  //   clearmotors();
  //   wait(.2, sec);

  //attack bar
  forwardPIDD(-200, 100);
  turnPID(100, 85, -1);
  forwardPIDD(-1500, 100);
  //end
}

void defensive() {
  // SCORE PRELOAD
  forwardPIDD(1500, 105);
	  clearmotors();
  turnPID(90, 95, -1); 
  intake.spin(reverse, 100, pct);
  forwardPIDD(400, 95);
	clearmotors();

  //GET TRIBAL IN CENTER OF BORDER
  intake.spin(forward, 100, pct);
  forwardPIDD(-500, 105);
	  clearmotors();
  turnPID(0, 95, -1);
  forwardPIDD(300, 95);

  // push over bar
  forwardPIDD(0,  100);
    clearmotors();
  turnPID(-90, 95, -1);
  intake.spin(reverse, 100, pct);
    sWings(false); // deploy wings to get other tribal as well and save time
  forwardPIDD(800, 105);
  sWings(true);

  // fold back up and get backbar tribal
    clearall();
  forwardPIDD(-200, 100);
	clearmotors();
  turnPID(45, 95, -1);
    clearall();
  forwardPIDD(-2000, 120);
  sWings(false);

  // spin to knock it out
  turnPID(360, 100, -1);
    clearall();
  // touch the bar
  forwardPIDD(0, 110);
  turnPID(-65, 90, -1);

  // Touch it 😈 hEE HEE HAW
  forwardPIDD(-1000, 100);

  // *end*
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  pre();
  thread a(sensordisplays);
}

/*---------------------------------------------------------------------------*/
/*                              Auton Task                                  */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  offensive();
}

/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {

// broken

//   // intakepistonb.set(true);
//   catapult.setStopping(hold);
//   stopBase();
//   float caxis1 = Controller1.Axis1.position(pct);
//   float caxis3 = Controller1.Axis3.position(pct);
//   float caxis1B = Controller1.Axis2.position(pct);

//  while (true) { 
//     if ((Controller1.Axis1.position(percent) > 5) or (Controller1.Axis1.position(percent) < -5)) {
//       caxis1B = 1.2 * pow (1.043, abs(Controller1.Axis1.position(pct))) - 1.2 + (0.2 * abs(Controller1.Axis1.position(pct)));
//     if(Controller1.Axis1.position(pct)>0){
//       caxis1 = caxis1B; }
//     if (Controller1.Axis1.position(pct)<0){
//       caxis1 = -caxis1B; }
//     if (Controller1.Axis1.position(pct)==0){
//       caxis1 = 0; }
//     else {
//       caxis1 = 0; }
//      if((Controller1.Axis3.position(percent) > 5) or (Controller1.Axis3.position(percent) < -5)){
//       caxis3 = Controller1.Axis3.position(); }
//     else{
//       caxis3 = 0; }
//     middleleft.spin(forward, (caxis3 + caxis1), percent);
//     middleright.spin(forward, (caxis3 - caxis1), percent);
//    frontleft.spin(reverse, (-caxis3 - caxis1), percent);
//     frontright.spin(reverse, (-caxis3 + caxis1), percent);
//     backright.spin(reverse, (-caxis3 + caxis1), percent);
//     backleft.spin(reverse, (-caxis3 - caxis1), percent);

//   if((Controller1.Axis3.position()>-5 && Controller1.Axis3.position()<5) && (Controller1.Axis1.position()>-5 && Controller1.Axis1.position()<5)){
//   stopBase();
//   }
//     if (Controller1.ButtonR2.pressing()) {
//       (intake.spin(reverse, 90, pct));
//     } else if (Controller1.ButtonR1.pressing()) {
//       (intake.spin(forward, 90, pct));
//     } else {
//       intake.stop();
//     }

//     if (Controller1.ButtonUp.pressing()) {
//       leftwing.set(false);
//       rightwing.set(false);
//     } else if (Controller1.ButtonLeft.pressing()) {
//       leftwing.set(true);
//       rightwing.set(true);
//     }
//   }
//  }

//   while (1) {

//     wait(20, msec); // Sleep the task for a short amount of time to
//                     // prevent wasted resources.
//   }
}

// Main will set up the competition functions and callbacks.

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
