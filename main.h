/*
File : main.h
Author : Daniel Finell & Benoît Gallois
Date : 6 may 2022
Initializes the devices we use and the threads.
*/

#ifndef MAIN_H
#define MAIN_H

#include "camera/dcmi_camera.h"				//A LAISSER OU PAS?
#include "msgbus/messagebus.h"
#include "parameter/parameter.h"

/* Defines the different states constants for the robot control switch. */
#define CRUISE_STATE					0
#define BYPASS_OBSTACLE_WALL			1
#define BYPASS_OBSTACLE_ANGLE_RIGHT		2
#define BYPASS_OBSTACLE_ANGLE_LEFT		3
#define BYPASS_U_TURN					4


/*Definition of the "setter". */
void set_robot_state(uint8_t new_state);


/** Robot wide IPC bus. */
extern messagebus_t bus;

extern parameter_namespace_t parameter_root;

void SendUint8ToComputer(uint8_t* data, uint16_t size);

#endif
