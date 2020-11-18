#include "main.h"
#include "X/control/robot.h"
using namespace pros;
////////////////////////////////////////////////////////////////////////////////
//pros:Motor base (port, gearset, direction)
//////////BASE MOTORS///////////////////////////////////////////////////////////
pros::Motor LeftFrontMotor (1, E_MOTOR_GEARSET_18, false);
pros::Motor RightFrontMotor (2, E_MOTOR_GEARSET_18, true);
pros::Motor LeftBackMotor (4,E_MOTOR_GEARSET_18, false);
pros::Motor RightBackMotor (7, E_MOTOR_GEARSET_18, true);
pros::Motor IntakeRight (13, E_MOTOR_GEARSET_18, false);
pros::Motor IntakeLeft (9, E_MOTOR_GEARSET_18, false);
pros::Motor ConveyorRight (8, E_MOTOR_GEARSET_06, true);
pros::Motor ConveyorLeft (15, E_MOTOR_GEARSET_06, true);
//////////CONTROLLER///////////////////////////////////////////////////////////
pros::Controller master (E_CONTROLLER_MASTER);
////////////////////////////////////////////////////////////////////////////////
//P.O.S. 11, 15, 19
