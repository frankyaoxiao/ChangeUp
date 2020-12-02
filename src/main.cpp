#include "main.h"
#include "X/robot.h"
#include "X/auton.h"
#include <iostream>
using namespace std;
using namespace pros;

/////////////////////////VARIABLES/////////////////////////////

extern int selectedAuton;
string currentMode;

bool fieldCentric = false;

double powerToRPMFactor = 100/127;
double degreeToRadianFactor = 3.1459/180;

vision_object_s_t ballInConveyor;
vision_signature_s_t redBallSignature = VisionSensor.signature_from_utility(1, 3733, 5807, 4770, 787, 2633, 1710, 4.700, 0);
vision_signature_s_t blueBallSignature = VisionSensor.signature_from_utility(2, -3855, -3035, -3445, 11431, 14689, 13060, 3.000, 0);

/////////////////////////FUNCTIONS/////////////////////////////

void initialize() {

  VisionSensor.clear_led();
  VisionSensor.set_exposure(150);
  VisionSensor.set_zero_point(E_VISION_ZERO_CENTER);
  ImuM.reset();
  pros::lcd::initialize();
  pros::lcd::set_text(1, "5327U");
  pros::lcd::register_btn0_cb(button0);
  pros::lcd::register_btn1_cb(button1);
  pros::lcd::register_btn2_cb(button2);
  currentMode = "Initialization";
};

void disabled() {

};

void competition_initialize() {

};

void autonomous() {
  currentMode = "Autonomous Period";
  master.rumble(".");
  if (selectedAuton == 1) {
    oneGoalAuton();
  }
  else if (selectedAuton == 2) {
    twoGoalAuton();
  }
  else if (selectedAuton == 3) {
		ImuM.reset();
		delay(2000);
    progSkills();
  }
  else {
    flipOutAuton();
  }
};

void opcontrol() {

  currentMode = "Driver Control";

	while (true) {

    updateBrainText();

		/////////////////////////DRIVE TRAIN CALCULATIONS/////////////////////////////

    double analogLeftX = master.get_analog(ANALOG_LEFT_X);
    double analogLeftY = master.get_analog(ANALOG_LEFT_Y);
    double analogRightX = master.get_analog(ANALOG_RIGHT_X) * 0.9;

    double heading = ImuM.get_heading() * (degreeToRadianFactor);

    double finalX = (analogLeftX * cos(heading)) + (analogLeftY * sin(heading));
    double finalY = (analogLeftX * sin(heading)) + (analogLeftY * cos(heading));

		if (fieldCentric == true) {
	    analogLeftX = finalX;
	    analogLeftY = finalY;
		}
		else {
			analogLeftX = master.get_analog(ANALOG_LEFT_X);
			analogLeftY = master.get_analog(ANALOG_LEFT_Y);
		}

		int LF = analogLeftX - analogLeftY + analogRightX;
		int RF = -analogLeftX - analogLeftY - analogRightX;
		int LB = analogLeftX - analogLeftY - analogRightX;
		int RB = -analogLeftX - analogLeftY + analogRightX;

		/////////////////////////BUTTONS AND MACROS/////////////////////////////

		if (master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
		    IntakeRight.move_voltage(12000);
		    IntakeLeft.move_voltage(-12000);

				}


        else if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
            IntakeRight.move_voltage(-12000);
            IntakeLeft.move_voltage(12000);

        }

        else {

            IntakeRight.move_voltage(0);
            IntakeLeft.move_voltage(0);
        }
        if (master.get_digital(E_CONTROLLER_DIGITAL_L1)) {

            ConveyorRight.move_voltage(-12000);
            ConveyorLeft.move_voltage(12000);
        }


        else if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) {

            ConveyorRight.move_voltage(12000);
            ConveyorLeft.move_voltage(-12000);
        }

        else if (master.get_digital(E_CONTROLLER_DIGITAL_X)) {

            ConveyorRight.move(-100);
            ConveyorLeft.move(100);
        }

        else if (master.get_digital(E_CONTROLLER_DIGITAL_A)) {

            ConveyorRight.move_voltage(-12000);
            ConveyorLeft.move_voltage(12000);
            IntakeRight.move_voltage(12000);
    		    IntakeLeft.move_voltage(-12000);
        }

        else if (master.get_digital(E_CONTROLLER_DIGITAL_B)) {

            ConveyorRight.move_voltage(12000);
            ConveyorLeft.move_voltage(-12000);
            IntakeRight.move_voltage(-12000);
    		    IntakeLeft.move_voltage(12000);
        }

        else {

            ConveyorRight.move_voltage(0);
            ConveyorLeft.move_voltage(0);
        }
			if (master.get_digital(E_CONTROLLER_DIGITAL_Y)){
				if (fieldCentric == true) {
					fieldCentric = false;
				}
			}
      if (master.get_digital(E_CONTROLLER_DIGITAL_UP)) {
        LF = -127;
        RF = -127;
        LB = -127;
        RB = -127;
      }
      else if (master.get_digital(E_CONTROLLER_DIGITAL_LEFT)) {
        LF = -127;
        RF = 127;
        LB = -127;
        RB = 127;
      }
      else if (master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
        LF = 127;
        RF = -127;
        LB = 127;
        RB = -127;
      }
      else if (master.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
        LF = 127;
        RF = 127;
        LB = 127;
        RB = 127;
      }

		/////////////////////////MOTOR MOVEMENTS/////////////////////////////

		LeftFrontMotor.move(LF);
		RightFrontMotor.move(RF);
		LeftBackMotor.move(-LB);
		RightBackMotor.move(-RB);

    /////////////////////////NOTIFICATIONS/////////////////////////////

    vision_object_s_t redBall = VisionSensor.get_by_sig(0, 1);
    vision_object_s_t blueBall = VisionSensor.get_by_sig(0, 2);

    int redBallArea = redBall.height * redBall.width;
    int blueBallArea = blueBall.height * blueBall.width;
    if (redBallArea > blueBallArea){
        VisionSensor.set_led(COLOR_RED);
    }
    else if (redBallArea < blueBallArea) {
        VisionSensor.set_led(COLOR_BLUE);
    }
    else {
      VisionSensor.set_led(COLOR_WHITE);
    };

    if ((redBallArea >= 1 || blueBallArea >= 1) && IntakeRight.get_target_velocity() > 10) {
      master.rumble(".");
    };

    pros::delay(10);

	}
};
