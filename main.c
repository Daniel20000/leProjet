/*
File : main.c
Author : Daniel Finell & Benoît Gallois
Date : 12 may 2022
Initializes the devices we use and the threads.
*/

#include <spi_comm.h>
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


    /* Initialization for RGB_LED. */
    spi_comm_start();


    /* Initialization MOTORS. */
	motors_init();


	chThdSleepMilliseconds(2000); 					// Waits 2 seconds to complete all the initializations and calibrations.

    /* Infinite loop. */
    while (1) {

    	/* Declarations of the different threads for the robot control. */
    	switch(state_of_robot){
    		case CRUISE_STATE:
    			move_forward();						// Basic Thread
    			break;
    		case BYPASS_U_TURN:
    		    u_turn_bypassing();					// If the robot detects that it is entering a dead end, it calls a thread to get out.
    			break;
    		case BYPASS_OBSTACLE_WALL:
    			wall_bypassing();					// If the robot detects a front obstacle, it turns right to avoid it.
    			break;
    		case BYPASS_OBSTACLE_ANGLE_RIGHT:
    		    angle_right_bypassing();			// If the robot detects an obstacle at 90° to its right, it goes around it.
    		    break;
    		case BYPASS_OBSTACLE_ANGLE_LEFT:
    		    angle_left_bypassing();				// If the robot detects an obstacle at 90° to its left, it goes around it.
    		    break;
    	}

        chThdSleepMilliseconds(100); 				// Waits 0,1 second.
    }
}


#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}
