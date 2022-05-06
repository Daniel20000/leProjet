/*
File : detect_obstacle.c
Author : Daniel Finell & Benoît Gallois
Date : 6 may 2022
Definition of the functions that they control the robot.
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
#include <sensors/proximity.h>
#include <sensors/imu.h>

#include <detect_obstacle.h>
#include <steep_slope.h>


/* Defines the speeds for the motors. */
#define CRUISING_SPEED          300
#define STOP_SPEED              0
#define TURN_SPEED			    600


/*
 * Functions that control the MOTORS.
 */

void go_straight_on(void){
	right_motor_set_speed(CRUISING_SPEED);
	left_motor_set_speed(CRUISING_SPEED);
	check_slope();
}

void turn_90_left(void){
	right_motor_set_speed(TURN_SPEED);
	left_motor_set_speed(STOP_SPEED);
	chThdSleepMilliseconds(TIME_TO_TURN);
	check_slope();
}

void turn_90_right(void){
	right_motor_set_speed(STOP_SPEED);
	left_motor_set_speed(TURN_SPEED);
	chThdSleepMilliseconds(TIME_TO_TURN);
	check_slope();
}

void stop_robot(void){
	right_motor_set_speed(STOP_SPEED);
	left_motor_set_speed(STOP_SPEED);
}

void backtracking(void){
	right_motor_set_speed(-CRUISING_SPEED);
	left_motor_set_speed(-CRUISING_SPEED);
	check_slope();
}


/*
 * Definition of the different threads.
 */

void move_forward(void){
	go_straight_on();
	if(((IR1 >= PROX_THRESHOLD) || (IR8 >= PROX_THRESHOLD)) && (IR2 <= 90)
			&& (IR7 <= 90) && (IR3 <= 90) && (IR6 <= 90)){
		set_led(LED1, ON);
		set_robot_state(BYPASS_OBSTACLE_WALL);
	}

	if(((IR1 >= PROX_THRESHOLD) || (IR8 >= PROX_THRESHOLD)) && (IR2 >= 120)
			&& (IR7 <= 120) && (IR3 >= 100) && (IR6 <= 100)){
		set_led(LED1, ON);
		set_led(LED3, ON);
		set_robot_state(BYPASS_OBSTACLE_ANGLE_RIGHT);
	}

	if(((IR1 >= PROX_THRESHOLD) || (IR8 >= PROX_THRESHOLD)) && (IR2 <= 90)
			&& (IR7 >= 90) && (IR3 <= 90) && (IR6 >= 90)){
			set_led(LED1, ON);
			set_led(LED7, ON);
			set_robot_state(BYPASS_OBSTACLE_ANGLE_LEFT);
		}

	if(((IR1 >= PROX_THRESHOLD) && (IR8 >= PROX_THRESHOLD)) && (IR2 >= 90)
			&& (IR7 >= 90) && (IR3 >= 90) && (IR6 >= 90)){
		set_led(LED1,ON);
		set_led(LED3,ON);
		set_led(LED7,ON);
		set_robot_state(BYPASS_U_TURN);
	}
}



void wall_bypassing(void){
	turn_90_right();
	clear_leds();
	while(IR6 >= PROX_THRESHOLD){
		go_straight_on();
	}
	chThdSleepMilliseconds(TIME_MARGIN);
	turn_90_left();
	go_straight_on();							//potentiellement à enlever
	set_robot_state(CRUISE_STATE);
}

void angle_right_bypassing(void){
	turn_90_left();
	clear_leds();
	go_straight_on();
	while(IR3 >= 100){
		go_straight_on();
	}
	chThdSleepMilliseconds(TIME_MARGIN);
	turn_90_right();
	go_straight_on();
	set_robot_state(CRUISE_STATE);
}

void angle_left_bypassing(void){
	turn_90_right();
	clear_leds();
	go_straight_on();
	while(IR6 >= 100){
		go_straight_on();
	}
	chThdSleepMilliseconds(TIME_MARGIN);
	turn_90_left();
	go_straight_on();
	set_robot_state(CRUISE_STATE);
}

void u_turn_bypassing(void){
	while((IR2 >= 63) && (IR7 >= 63)){
		clear_leds();
		set_front_led(ON);
		backtracking();
	}
	set_front_led(OFF);
	turn_90_left();
	go_straight_on();
	set_robot_state(CRUISE_STATE);
}








