#include "main.h"
#include <iostream>

using namespace std;
using namespace pros;

/////////////autonfunctions.cpp///////////////
extern void button0();
extern void button1();
extern void button2();

extern void baseMovement(int x_direction, int y_direction, int turn);
extern void rollerMovement(int conveyorDirection, int intakeDirection);
extern void timeBasedMovement(int x_direction, int y_direction, int turn, int conveyorDirection, int intakeDirection);
extern void oneGoalAuton();
extern void twoGoalAuton();
extern void progSkills();
extern void flipOutAuton();
