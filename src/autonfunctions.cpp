#include "main.h"
#include "X/robot.h"
#include "X/auton.h"
#include <iostream>
using namespace std;
using namespace pros;

int selectedAuton = 1;

void button0(){
  selectedAuton = 0;
  pros::lcd::set_text(2, "Selected Autonomous: Flip-Out");
};

void button1(){
  selectedAuton = 1;
  pros::lcd::set_text(2, "Selected Autonomous: 1 Goal");
};

void button2(){
  selectedAuton = 2;
  pros::lcd::set_text(2, "Selected Autonomous: 2 Goal");
};

void baseMovement(int x_direction, int y_direction, int turn){
  int leftFront = x_direction - y_direction + turn;
  int rightFront = -x_direction - y_direction - turn;
  int leftBack = x_direction - y_direction - turn;
  int rightBack = -x_direction - y_direction + turn;
  LeftFrontMotor.move(leftFront);
  RightFrontMotor.move(rightFront);
  LeftBackMotor.move(-leftBack);
  RightBackMotor.move(-rightBack);
}

void rollerMovement(int conveyorDirection, int intakeDirection){
  ConveyorRight.move_voltage(-12000 * conveyorDirection);
  ConveyorLeft.move_voltage(12000 * conveyorDirection);
  IntakeRight.move_voltage(-12000 * intakeDirection);
  IntakeLeft.move_voltage(12000 * intakeDirection);
}

void timeBasedMovement(int x_direction, int y_direction, int turn, int conveyorDirection, int intakeDirection){

    baseMovement(x_direction, y_direction, turn);
    rollerMovement(conveyorDirection, intakeDirection);

  };

  class Odom {
  public:
      bool IsRunning;
      double currentX;
      double currentY;
      double previousXLeft;
      double previousXRight;
      double previousY;
      double theta;

      void Track() {

              theta = ImuM.get_heading();
              double thetaRad = theta * 3.14159 / 180;

              double CurrentXLeftEncoder = LEncoder.get_value();
              double CurrentXRightEncoder = REncoder.get_value();
              double CurrentYEncoder = MEncoder.get_value();

              double deltaXRight = CurrentXRightEncoder - previousXRight;
              double deltaXLeft = CurrentXLeftEncoder - previousXLeft;
              double deltaY = CurrentYEncoder - previousY;

              double offsetX = ((deltaXLeft + deltaXRight) / 2) * sin(thetaRad) + deltaY * cos(thetaRad);
              double offsetY = ((deltaXLeft + deltaXRight) / 2) * cos(thetaRad) - deltaY * sin(thetaRad);

              previousXLeft = CurrentXLeftEncoder;
              previousXRight = CurrentXRightEncoder;
              previousY = CurrentYEncoder;

              currentX += offsetX;
              currentY += offsetY;
      }

      void MoveTo(double posX, double posY, double conveyor, double intake) {
          Track();
          IsRunning = true;
          double errorX = posX - currentX;
          double WantedAngleRad = atan((posY - currentY) / (posX - currentX));
          double WantedAngle = WantedAngleRad * 180 / 3.14159;
          double errorTheta = WantedAngle - theta;
          IntakeRight.move(intake);
          IntakeLeft.move(-intake);
          ConveyorRight.move(-conveyor);
          ConveyorLeft.move(conveyor);


          while (errorTheta > .5) {
              Track();
              if (theta - WantedAngle >= 180) {
                  baseMovement(0, 0, -100);
                  errorTheta = WantedAngle - theta;
                  pros::delay(10);
              }
              else {

                  baseMovement(0, 0, -100);
                  errorTheta = WantedAngle - theta;
                  pros::delay(10);
              }

          }
          baseMovement(0, 0, 0);
          while (errorX > .5) {
              Track();

              baseMovement(100, 0, 0);
              errorX = posX - currentX;
              pros::delay(10);
              }


          baseMovement(0, 0, 0);
          IntakeRight.move(0);
          IntakeLeft.move(0);
          ConveyorRight.move(0);
          ConveyorLeft.move(0);
          Track();
      }
  };


void oneGoalAuton(){
  timeBasedMovement(0, 0, 0, -1, 0);
  delay(100);
  timeBasedMovement(0, 0, 0, 1, 0);
  delay(1500);
  timeBasedMovement(0, 0, 0, -1, 0);
  delay(150);
  timeBasedMovement(0, 0, 0, 1, 0);
  delay(1500);
  timeBasedMovement(0, 0, 0, -1, 0);
  delay(150);
  timeBasedMovement(0, 0, 0, 1, 0);
  delay(1500);
  timeBasedMovement(0, 0, -100, 0, 0);
  delay(500);
  timeBasedMovement(0, -127, 0, 0, 1);
  delay(1500);
  timeBasedMovement(0, 0, 0, 0, 0);
};

void twoGoalAuton(){
  timeBasedMovement(0, 0, 0, -1, 0);
  delay(100); //0.3
  timeBasedMovement(0, 0, 0, 1, 0);
  delay(1500); //1.8
  timeBasedMovement(0, 0, 0, -1, 0);
  delay(150); //1.95
  timeBasedMovement(0, 0, 0, 1, 0);
  delay(4000); //5.95
  timeBasedMovement(0, 0, -100, 0, 0);
  delay(500); //6.45
  timeBasedMovement(0, -100, 0, 0, 1);
  delay(1500); //6.95
  timeBasedMovement(0, 0, -100, 0, 0);
  delay(500); //7.45
  timeBasedMovement(40, 0, 0, 0, 0);
  delay(750);
  timeBasedMovement(0,95,0,1,1);
  delay(1500); //8.45
  timeBasedMovement(0,0,0,1,1);
  delay(1500); //9.95
  timeBasedMovement(0,0,0,-1,1);
  delay(150); //10.1
  timeBasedMovement(0,0,0,1,1);
  delay(1000); //11.1
  timeBasedMovement(0,0,100,0,0);
  delay(500); //11.6
  timeBasedMovement(0,-50,0,0,0);
  delay(500); //12.1
  timeBasedMovement(0,0,0,0,0);
};

void progSkills() {

};

void flipOutAuton() {
  timeBasedMovement(0,0,0,-1,1);
  delay(500);
  timeBasedMovement(0,0,0,0,0);
};
