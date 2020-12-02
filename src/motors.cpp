#include "main.h"
#include "X/robot.h"
#include <iostream>
using namespace pros;
////////////////////////////////////////////////////////////////////////////////
//pros:Motor base (port, gearset, direction)
//////////BASE MOTORS///////////////////////////////////////////////////////////
pros::Motor LeftFrontMotor (1, E_MOTOR_GEARSET_18, false);
pros::Motor RightFrontMotor (2, E_MOTOR_GEARSET_18, true);
pros::Motor LeftBackMotor (4,E_MOTOR_GEARSET_18, false);
pros::Motor RightBackMotor (7, E_MOTOR_GEARSET_18, true);
pros::Motor IntakeRight (14, E_MOTOR_GEARSET_18, false);
pros::Motor IntakeLeft (9, E_MOTOR_GEARSET_18, false);
pros::Motor ConveyorRight (8, E_MOTOR_GEARSET_06, true);
pros::Motor ConveyorLeft (16, E_MOTOR_GEARSET_06, true);
//////////SENSORS///////////////////////////////////////////////////////////
pros::Imu ImuM(20);
pros::ADIEncoder LEncoder(3, 4, true);
pros::ADIEncoder REncoder(5, 6);
pros::ADIEncoder MEncoder(7, 8);
pros::Vision VisionSensor(13);
//////////CONTROLLER///////////////////////////////////////////////////////////
pros::Controller master (E_CONTROLLER_MASTER);
////////////////////////////////////////////////////////////////////////////////
//P.O.S. 11, 15, 19
