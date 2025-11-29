#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep

extern pros::MotorGroup left_motor_group;  // left side motors front to back 
extern pros::MotorGroup right_motor_group; // right side motors front to back

extern pros::Motor intake;
extern pros::Motor lwm;
extern pros::Motor hood;

extern pros::Rotation odom;
extern pros::Imu imu;

extern lemlib::TrackingWheel vertical_tracking_wheel;

extern lemlib::Drivetrain drivetrain;

extern lemlib::OdomSensors sensors;

// lateral PID controller
extern lemlib::ControllerSettings lateral_controller;

// angular PID controller
extern lemlib::ControllerSettings angular_controller;

// input curve for throttle input during driver control
extern lemlib::ExpoDriveCurve throttle_curve;

// input curve for steer input during driver control
extern lemlib::ExpoDriveCurve steer_curve;

// create the chassis
extern lemlib::Chassis chassis;


