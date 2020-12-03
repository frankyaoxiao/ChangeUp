#include "main.h"
#include "X/robot.h"
#include "X/auton.h"
#include <iostream>
using namespace std;
using namespace pros;

extern string currentMode;
extern int selectedAuton;

void updateBrainText(){
  pros::lcd::set_text(1, "5327U (" + currentMode + ")");
  if (selectedAuton == 0) {
      pros::lcd::set_text(2, "Selected Autonomous: Flip-Out");
  }
  else if (selectedAuton == 1) {
      pros::lcd::set_text(2, "Selected Autonomous: 1 Goal");
  }
  else if (selectedAuton == 2) {
      pros::lcd::set_text(2, "Selected Autonomous: 2 Goal");
  }
  else if (selectedAuton == 3) {
      pros::lcd::set_text(2, "Selected Autonomous: Programming Skills");
  };
  pros::lcd::set_text(3, "Heading: " + to_string(ImuM.get_heading()) + " degrees");
  double encoderAverage = (LEncoder.get_value() + REncoder.get_value())/2;
  pros::lcd::set_text(4, "X Encoder Ticks: " + to_string(encoderAverage) + " ticks");
};
