/*
File : steep_slope.c
Author : Daniel Finell & Benoît Gallois
Date : 6 may 2022
Definition of function if a steep slope is detected.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ch.h"
#include "hal.h"
#include <motors.h>
#include <leds.h>
#include <sensors/imu.h>

#include <main.h>
#include <steep_slope.h>
#include <detect_obstacle.h>


/* Defines the acceleration axis. */
#define X						get_acc(0)
#define Y						get_acc(1)

/* Defines the threshold for the IMU. */
#define SLOPE_THRESHOLD			6000

/*
 * Definition of the functions to set or clear the LED and RGB_LED in the same time.
 */

void set_all_rgb_led(uint8_t red_val, uint8_t green_val, uint8_t blue_val) {
	rgb_led_name_t rgb_led_list[4] = { LED2, LED4, LED6, LED8 };
	for(int i = 0 ; i <= 3 ; i = i + 1){
		set_rgb_led(rgb_led_list[i], red_val, green_val, blue_val);
	}
}

void clear_all_rgb_led(void){
	led_name_t led_list[4] = { LED2, LED4, LED6, LED8 };
		for(int i = 0 ; i <= 3 ; i = i + 1){
			set_rgb_led(led_list[i], OFF, OFF, OFF);
		}
}

void set_all_led(uint8_t value) {
	led_name_t led_list[4] = { LED1, LED3, LED5, LED7 };
	for(int i = 0 ; i <= 3 ; i = i + 1){
		set_led(led_list[i],value);
	}
}


/*
 * Definition of the functions that check the slope and put the robot in alert mode if slope too steep.
 */

void check_slope(void){
	if(X > SLOPE_THRESHOLD || X < -SLOPE_THRESHOLD || Y > SLOPE_THRESHOLD || Y < -SLOPE_THRESHOLD){		/* Check the inclination of the two axis
																										that can make the robot fall. */
		steep_slope_warning();																			//Call the warning function.
	}
}

void steep_slope_warning(void){
	stop_robot();
	while(X > SLOPE_THRESHOLD || X < -SLOPE_THRESHOLD || Y > SLOPE_THRESHOLD || Y < -SLOPE_THRESHOLD){	//Set of led to warn the user.
		
		//prends juste ces deux prochains paragraphes:
		
		//circle  blinking
		for(int i = 0 ; i <= 3 ; i = i + 1){
			set_led(led_list[i],ON);
			chThdSleepMilliseconds(300);
			set_led(led_list[i],OFF);
			set_rgb_led(rgb_led_list[i], ON, OFF, ON);
			chThdSleepMilliseconds(300);
			set_rgb_led(rgb_led_list[i], OFF, OFF, OFF);
			
		}

		//alternate red blinking
		set_all_led(OFF);
		set_all_rgb_led(OFF, OFF, RGB_MAX_INTENSITY);
		chThdSleepMilliseconds(300);
		clear_all_rgb_led();
		set_all_led(ON);
		chThdSleepMilliseconds(300);
	}
	clear_all_rgb_led();
	set_robot_state(CRUISE_STATE);
}
