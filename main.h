/*
File : main.h
Author : Daniel Finell & Benoît Gallois
Date : 12 may 2022
Initializes the devices we use and the threads.
*/

#ifndef MAIN_H
#define MAIN_H

#include <camera/dcmi_camera.h>
#include <msgbus/messagebus.h>
#include <parameter/parameter.h>


/* Defines the different states constants for the robot control switch. */
#define CRUISE_STATE					0
#define BYPASS_U_TURN					1
#define BYPASS_OBSTACLE_WALL			2
#define BYPASS_OBSTACLE_ANGLE_RIGHT		3
#define BYPASS_OBSTACLE_ANGLE_LEFT		4


/**
 * @brief   Allows you to change the value of state_of_robot in the other files.
 *
 * @param new_state      0-4, respectively CRUISE_STATE, BYPASS_U_TURN, BYPASS_OBSTACLE_WALL, BYPASS_OBSTACLE_ANGLE_RIGHT, BYPASS_OBSTACLE_ANGLE_LEFT.
 *
 */
void set_robot_state(uint8_t new_state);


/** Robot wide IPC bus. */
extern messagebus_t bus;

extern parameter_namespace_t parameter_root;

#endif
