#include "main.h"
#include "X/control/robot.h"
#include "X/odometry/odometry.h"
#include <iostream>

pros::Imu ImuM(20);
pros::ADIEncoder LEncoder(3, 4, true);
pros::ADIEncoder REncoder(5, 6);
pros::ADIEncoder MEncoder(7, 8);

class Odom{
public:
  bool IsRunning;
  double currentX;
  double currentY;
  double previousXLeft;
  double previousXRight;
  double previousY;

  void Track() {
    IsRunning = true;
    while(IsRunning){
      double theta = ImuM.get_heading();

      double CurrentXLeftEncoder = LEncoder.get_value();
      double CurrentXRightEncoder = REncoder.get_value();
      double CurrentYEncoder = MEncoder.get_value();

      double deltaXRight = CurrentXRightEncoder - previousXRight;
      double deltaXLeft = CurrentXLeftEncoder - previousXLeft;
      double deltaY = CurrentYEncoder - previousY;

      double offsetX = ((deltaXLeft + deltaXRight) / 2) * cos(theta) + deltaY * sin(theta);
      double offsetY = ((deltaXLeft + deltaXRight) / 2) * sin(theta) - deltaY * cos(theta);

      previousXLeft = CurrentXLeftEncoder;
      previousXRight = CurrentXRightEncoder;
      previousY = CurrentYEncoder;

      currentX += offsetX;
      currentY += offsetY;

      pros::delay(10);

    }

  }

};
