#include "main.h"
#include <iostream>

using namespace std;
using namespace pros;

extern pros::Motor LeftFrontMotor;
extern pros::Motor RightFrontMotor;
extern pros::Motor LeftBackMotor;
extern pros::Motor RightBackMotor;
extern pros::Motor IntakeRight;
extern pros::Motor IntakeLeft;
extern pros::Motor ConveyorRight;
extern pros::Motor ConveyorLeft;
extern pros::Controller master;
extern pros::Imu ImuM;
extern pros::ADIEncoder LEncoder;
extern pros::ADIEncoder REncoder;
extern pros::ADIEncoder MEncoder;
extern pros::Vision VisionSensor;

extern void updateBrainText();
extern void ballDetection();
