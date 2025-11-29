#include "main.h"
#include "lemlib/api.hpp"
#include "config.hpp"

void pidLateralTune() {
    // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    // move 48" forwards
    chassis.moveToPoint(0, 48, 10000);
};


void pidAngularTune() {
    // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    // turn to face heading 90 with a very long timeout
    chassis.turnToHeading(90, 100000);
};

void autoRight() {
    chassis.setPose(0, 10, 0);                                                  // reset starting pos

    lwm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);                               // hold lwm up
    intake.move(127);                                                           // spin intake

    chassis.moveToPoint(12, 42, 1500);                                          // go to 3 blocks in the middle
    pros::delay(150);
    
    lwm.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);                              // lwm down for the 3 blocks
    lwm.move(127);
    pros::delay(300);
    lwm.move_velocity(0);

    chassis.moveToPoint(30, 14, 2000, {.forwards = false, .maxSpeed = 70});     // go to an intermediate point
    chassis.turnToHeading(180, 1000, {.maxSpeed = 70});                                              // turn to loader

    pros::delay(100);
    chassis.moveToPoint(29, 32, 2000, {.forwards = false, .maxSpeed = 80});     // go to long goal
    pros::delay(1000);
    intake.move(-127);                                                          // reverse blocks to prevent jamming
    pros::delay(100);                                                           // wait
    intake.move(127);                                                           // score blocks
    hood.move(127);
    pros::delay(2000);
    hood.move_velocity(0);

    chassis.moveToPoint(27.5, 1, 2000, {.maxSpeed = 70});                                           // go to loader
    pros::delay(2000);                                                           // wait to intake blocks from loader
    chassis.moveToPoint(30, 32, 1000, {.forwards = false});                                           // go back a bit in case lwm is jamming
    pros::delay(2000);
    intake.move(127);
    hood.move(127);
    pros::delay(1900);
    hood.move_velocity(0);
    chassis.moveToPoint(30, 25, 1000);
    chassis.moveToPoint(30, 32, 1000);
};

void autoLeft() {
    chassis.setPose(0, 10, 0);                                                  // reset starting pos

    lwm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);                               // hold lwm up
    intake.move(127);                                                           // spin intake

    chassis.moveToPoint(-12, 42, 1500);                                          // go to 3 blocks in the middle
    pros::delay(150);
    
    lwm.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);                              // lwm down for the 3 blocks
    lwm.move(127);
    pros::delay(300);
    lwm.move_velocity(0);

    chassis.moveToPoint(-34, 14, 2000, {.forwards = false, .maxSpeed = 70});     // go to an intermediate point
    chassis.turnToHeading(180, 1000, {.maxSpeed = 70});                                              // turn to loader

    pros::delay(100);
    chassis.moveToPoint(-33, 32, 2000, {.forwards = false, .maxSpeed = 80});     // go to long goal
    pros::delay(1000);
    intake.move(-127);                                                          // reverse blocks to prevent jamming
    pros::delay(100);                                                           // wait
    intake.move(127);                                                           // score blocks
    hood.move(127);
    pros::delay(2000);
    hood.move_velocity(0);

    chassis.moveToPoint(-33, 0, 2000, {.maxSpeed = 70});                                           // go to loader
    pros::delay(2000);                                                           // wait to intake blocks from loader
    chassis.moveToPoint(-34, 32, 1000, {.forwards = false});                                           // go back a bit in case lwm is jamming
    pros::delay(2000);
    intake.move(127);
    hood.move(127);
    pros::delay(1900);
    hood.move_velocity(0);
    chassis.moveToPoint(-34, 25, 1000);
    chassis.moveToPoint(-34, 32, 1000);
};

void sawpRight() {
    chassis.setPose(0, 10, 90);                                                 // reset position

    intake.move(127);                                                           // run intake
    lwm.move(127);                                                              // move lwm down
    pros::delay(220);
    lwm.move_velocity(0);

    chassis.moveToPoint(32.5, 10, 1000);                                        // go towards loader
    chassis.turnToHeading(180, 900, {.maxSpeed = 70});                          // face loader

    chassis.moveToPoint(32.5, 1.2, 2000);                                       // go into loader
    pros::delay(950);                                                           // wait for blocks to intake

    chassis.moveToPoint(32.5, 32, 2000, {.forwards = false});                   // go to long goal
    pros::delay(850);                                                           // wait until the robot is at the long goal
    intake.move(127);                                                           // score loader blocks into long goal
    hood.move(127);

    lwm.move(-127);                                                             // lift lwm up
    pros::delay(600);
    lwm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD); 
    lwm.move_velocity(0);
    pros::delay(900);                                                           // wait for blocks to finish scoring

    hood.move_velocity(0);                                                      // stop scoring
    chassis.turnToHeading(-90, 1000);                                           // turn to the left
    chassis.moveToPoint(-31, 26, 2000, {.maxSpeed = 70});                       // go to all 6 blocks in the middle

    lwm.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    lwm.move(127);                                                              // collect first set of blocks
    pros::delay(300);
    lwm.move_velocity(0);
    pros::delay(100);
    lwm.move(-127);                                                             // lift lwm up
    pros::delay(400);
    lwm.move_velocity(0);

    pros::delay(450);
    lwm.move(127);                                                              // collect second set of blocks
    pros::delay(300);
    lwm.move_velocity(0);

    chassis.turnToHeading(-135, 600);                                           // turn to middle goal
    chassis.moveToPoint(-25, 35, 1000, {.forwards = false});                    // go to middle goal
    intake.move(-100);
    pros::delay(130);
    intake.move(127);                                                           // score blocks
    hood.move(127);

    pros::delay(450);                                                           // wait for block to finish scoring
    hood.move_velocity(0);                                                      // stop scoring
    intake.move_velocity(0);
    chassis.moveToPoint(-59, 9, 1300);                                         // go to point in between loader and long goal
    chassis.turnToHeading(180, 600);                                            // turn towards long goal
    chassis.moveToPoint(-59, 30, 2000, {.forwards = false});                    // go to long goal

    pros::delay(50);
    intake.move(-127);
    pros::delay(50);
    intake.move(127);                                                           // score in long goal
    hood.move(127);
};

void autoSkills() {
    chassis.setPose(0, 10, 90);                                                 // reset position

    intake.move(127);                                                           // run intake
    lwm.move(127);                                                              // move lwm down
    pros::delay(180);
    lwm.move_velocity(0);

    chassis.moveToPoint(32.8, 10, 1000);                                        // go towards loader
    chassis.turnToHeading(180, 900, {.maxSpeed = 70});                          // face loader

    chassis.moveToPoint(32.8, 1.2, 2000);                                       // go into loader
    pros::delay(2000);
    chassis.moveToPoint(32.8, 2, 300, {.forwards = false});
    pros::delay(2000);

    chassis.moveToPoint(32.5, 14, 2000, {.forwards = false});
    pros::delay(100);
    chassis.turnToHeading(-135, 1000);
    chassis.moveToPoint(45, 26, 2000, {.forwards = false});

    pros::delay(100);
    chassis.turnToHeading(180, 1000);
    intake.move_velocity(0);
    chassis.moveToPoint(45, 94, 4000, {.forwards = false});
    lwm.move(-127);
    pros::delay(600);
    lwm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    lwm.move_velocity(0);
    pros::delay(100);
    chassis.moveToPoint(32.9, 98, 2000, {.forwards = false});
    chassis.turnToHeading(0, 1000);
    chassis.moveToPoint(34.5, 85, 1000, {.forwards = false});
    pros::delay(1000);
    intake.move(-127);
    pros::delay(300);
    intake.move(127);
    hood.move(127);
    pros::delay(5000);
    hood.move_velocity(0);

    lwm.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    lwm.move(127);
    pros::delay(200);
    lwm.move_velocity(0);

    pros::delay(500);
    chassis.moveToPoint(34, 118.5, 2000, {.maxSpeed = 80});
    pros::delay(2000);
    chassis.moveToPoint(34, 118, 500);
    pros::delay(2000);

    chassis.moveToPoint(34.7, 85, 2000, {.forwards = false});

    pros::delay(1200);

    intake.move(-127);
    pros::delay(200);
    hood.move(127);
    intake.move(127);

    pros::delay(5000);
    lwm.move(-127);
    pros::delay(450);
    lwm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    pros::delay(500);
    chassis.moveToPoint(48, 95, 2000);
    chassis.turnToHeading(-10, 1000);
    chassis.moveToPoint(50, -5, 5000, {.forwards = false, .maxSpeed = 90});

    pros::delay(5000);
    chassis.setPose(0, 0, 0);
    chassis.moveToPoint(-20, 20, 2000);
    chassis.turnToHeading(-90, 1000);
    chassis.moveToPoint(-80, -12, 2500);
};

