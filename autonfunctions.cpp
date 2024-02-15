// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// gyroo                inertial      7               
// intake               motor         15              
// catapult             motor         20              
// leftwing             digital_out   A               
// intakepistonb        digital_out   B               
// rightwing            digital_out   H               
// Controller1          controller                    
// RotationRight        rotation      21              
// RotationLeft         rotation      18              
// Opticall             optical       2               
// backleft             motor         17              
// middleleft           motor         16              
// frontleft            motor         12              
// backright            motor         14              
// middleright          motor         13              
// frontright           motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----

// void autofire() {
//   while (true) {
//   if (Opticall.hue() < 105 && Opticall.hue() > 65) {
//     catapult.spin(forward, 50, pct);
//     Brain.Screen.print("Hue: %.2f", Opticall.hue());
//     Brain.Screen.setCursor(2,2);
//   }
//   else {
//     catapult.stop();
//     Brain.Screen.print("Hue: %.2f", Opticall.hue());
//     Brain.Screen.setCursor(2,2);
//   }
// }
//   wait(10, msec);
//   Brain.Screen.clearScreen();
// }