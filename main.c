/*
File : main.c
Author : Daniel Finell & Benoît Gallois
Date : 6 may 2022
Initializes the devices we use and the threads.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ch.h"
#include "hal.h"
#include "spi_comm.h"
#include <motors.h>
#include <leds.h>
#include <sensors/imu.h>
#include <sensors/proximity.h>

#include <main.h>
#include <detect_obstacle.h>
#include <steep_slope.h>


/* Declaration of a global variable, and implementation of a "set" to give access to state_of_robot in other files. */
static uint8_t state_of_robot = 0;

void set_robot_state(uint8_t new_state){
	state_of_robot = new_state;
}


/* Initialization of the bus for sensors. */
messagebus_t bus;
MUTEX_DECL(bus_lock);
CONDVAR_DECL(bus_condvar);


int main(void)
{
	/* System init */
    halInit();
    chSysInit();

    /* Inits the Inter Process Communication bus. */
    messagebus_init(&bus, &bus_lock, &bus_condvar);


    /* Initialization PROXIMITY SENSORS. */
    proximity_start();
    calibrate_ir();


    /* Initialization IMU. */
    imu_start();
    calibrate_acc();


    /* Initialization RGB_LED. */
    spi_comm_start();


    /* Initialization MOTORS. */
	motors_init();

	chThdSleepMilliseconds(2000); 					//Waits 2 seconds.

    /* Infinite loop. */
    while (1) {

    	/* Declarations of the different threads for the robot control. */
    	switch(state_of_robot){
    		case CRUISE_STATE:
    			move_forward();						//Basic Thread
    			break;
    		case BYPASS_OBSTACLE_WALL:
    			wall_bypassing();
    			break;
    		case BYPASS_OBSTACLE_ANGLE_RIGHT:
    		    angle_right_bypassing();
    		    break;
    		case BYPASS_OBSTACLE_ANGLE_LEFT:
    		    angle_left_bypassing();
    		    break;
    		case BYPASS_U_TURN:
    			u_turn_bypassing();
    			break;
    	}

        chThdSleepMilliseconds(100); 				//Waits 0,2 second.
    }
}


#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}
