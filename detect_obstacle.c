#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ch.h"
#include "hal.h"
#include <usbcfg.h>
#include <main.h>
#include <motors.h>
#include <chprintf.h>
#include <leds.h>
#include <sensors/proximity.h>
#include <sensors/imu.h>


//definition of the usual speed
#define CRUISING_SPEED          300
#define STOP_SPEED              0
#define TURN_SPEED			    600

//definition of the IR sensors
#define IR1         		 	get_prox(0)
#define IR2           			get_prox(1)
#define IR3			   			get_prox(2)
#define IR4         		 	get_prox(3)
#define IR5           			get_prox(4)
#define IR6			   			get_prox(5)
#define IR7         		 	get_prox(6)
#define IR8           			get_prox(7)

//definition states of LED
#define OFF						0
#define ON						1

//definition acceleration axis
#define X						get_acc(0)
#define Y						get_acc(1)

//definition of threshhold
#define SLOPE_THRESHOLD				4200
#define PROX_THRESHOLD				100
#define PROX_UTURN_TRESH			100
#define TIME_TO_TURN				1075
#define TIME_MARGIN					250




/*
 * Differentes fonctions qui permettent au robot de se déplacer
 */

void go_straight_on(void){
	right_motor_set_speed(CRUISING_SPEED);
	left_motor_set_speed(CRUISING_SPEED);
}

void turn_90_left(void){
	right_motor_set_speed(TURN_SPEED);
	left_motor_set_speed(STOP_SPEED);
	chThdSleepMilliseconds(TIME_TO_TURN);
}

void turn_90_right(void){
	right_motor_set_speed(STOP_SPEED);
	left_motor_set_speed(TURN_SPEED);
	chThdSleepMilliseconds(TIME_TO_TURN);
}

void stop_robot(void){
	right_motor_set_speed(STOP_SPEED);
	left_motor_set_speed(STOP_SPEED);
}

void backtracking(void){
	right_motor_set_speed(-CRUISING_SPEED);
	left_motor_set_speed(-CRUISING_SPEED);
}


/*
 * Definition fonction toggle led
 */

void clear_rgb_led(void){
	set_rgb_led(LED2, OFF, OFF, OFF);
	set_rgb_led(LED4, OFF, OFF, OFF);
	set_rgb_led(LED6, OFF, OFF, OFF);
	set_rgb_led(LED8, OFF, OFF, OFF);
}

/*
 * Definition des fonctions principales
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

	if(X > SLOPE_THRESHOLD || X < -SLOPE_THRESHOLD || Y > SLOPE_THRESHOLD || Y < -SLOPE_THRESHOLD){
		set_robot_state(CAUTION_STEEP_SLOPE);
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
	go_straight_on();
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
	while((IR2 >= 57) && (IR7 >= 57)){
		clear_leds();
		set_front_led(ON);
		backtracking();
	}
	set_front_led(OFF);
	turn_90_left();
	go_straight_on();
	set_robot_state(CRUISE_STATE);
}


void steep_slope_warning(void){
	while(X > SLOPE_THRESHOLD || X < -SLOPE_THRESHOLD || Y > SLOPE_THRESHOLD || Y < -SLOPE_THRESHOLD){
		toggle_rgb_led(LED2, BLUE_LED, RGB_MAX_INTENSITY);
		toggle_rgb_led(LED4, BLUE_LED, RGB_MAX_INTENSITY);
		toggle_rgb_led(LED6, BLUE_LED, RGB_MAX_INTENSITY);
		toggle_rgb_led(LED8, BLUE_LED, RGB_MAX_INTENSITY);
		stop_robot();
	}
	clear_rgb_led();
	set_robot_state(CRUISE_STATE);
}


//chprintf((BaseSequentialStream *)&SDU1, "%d ", IR1);










