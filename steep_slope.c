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
#include <main.h>
#include <motors.h>
#include <leds.h>
#include <sensors/proximity.h>			//a enlever?
#include <sensors/imu.h>

#include <steep_slope.h>
#include <detect_obstacle.h>


/*
 * Definition of the function that clear all the RGB_LEDs.
 */

void clear_rgb_led(void){
	set_rgb_led(LED2, OFF, OFF, OFF);
	set_rgb_led(LED4, OFF, OFF, OFF);
	set_rgb_led(LED6, OFF, OFF, OFF);
	set_rgb_led(LED8, OFF, OFF, OFF);
}

void toggle_led(led_name_t led_number) {
	set_led(led_number,ON);
	chThdSleepMilliseconds(500);
	set_led(led_number,OFF);
}








void check_slope(void){
	if(X > SLOPE_THRESHOLD || X < -SLOPE_THRESHOLD || Y > SLOPE_THRESHOLD || Y < -SLOPE_THRESHOLD){
		steep_slope_warning();
	}
}


void steep_slope_warning(void){
	stop_robot();
	while(X > SLOPE_THRESHOLD || X < -SLOPE_THRESHOLD || Y > SLOPE_THRESHOLD || Y < -SLOPE_THRESHOLD){
		toggle_rgb_led(LED2, BLUE_LED, RGB_MAX_INTENSITY);
		toggle_rgb_led(LED4, BLUE_LED, RGB_MAX_INTENSITY);
		toggle_rgb_led(LED6, BLUE_LED, RGB_MAX_INTENSITY);
		toggle_rgb_led(LED8, BLUE_LED, RGB_MAX_INTENSITY);
		chThdSleepMilliseconds(500);
		set_led(LED1,ON);
		set_led(LED3,ON);
		set_led(LED5,ON);
		set_led(LED7,ON);
		chThdSleepMilliseconds(500);     //modifier la freq
		set_led(LED1,OFF);
		set_led(LED3,OFF);
		set_led(LED5,OFF);
		set_led(LED7,OFF);
	}
	clear_rgb_led();
	set_robot_state(CRUISE_STATE);
}
