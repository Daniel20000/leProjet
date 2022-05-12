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
#include <motors.h>
#include <leds.h>
#include <sensors/proximity.h>

#include <main.h>
#include <detect_obstacle.h>
#include <steep_slope.h>


/* Defines the speeds for the motors. */
#define CRUISING_SPEED          300
#define STOP_SPEED              0
#define TURN_SPEED			    600


/* Defines the IR sensors name. */
#define IR1         		 	get_prox(0)
#define IR2           			get_prox(1)
#define IR3			   			get_prox(2)
#define IR4         		 	get_prox(3)
#define IR5           			get_prox(4)
#define IR6			   			get_prox(5)
#define IR7         		 	get_prox(6)
#define IR8           			get_prox(7)


/* Defines the thresholds for the IR SENSORS. */
#define PROX_THRESHOLD_1		118				//mode sombre 100
#define PROX_THRESHOLD_2		140				//mode sombre 120
#define PROX_THRESHOLD_3		105				//mode sombre 90
#define PROX_THRESHOLD_BACK		75				//mode sombre 65


/* Defines the time constants.*/
#define TIME_TO_TURN			1075
#define TIME_MARGIN				250


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

/* Main thread. */
void move_forward(void){
	go_straight_on();
	if(((IR1 >= PROX_THRESHOLD_1) && (IR8 >= PROX_THRESHOLD_1)) && (IR2 >= PROX_THRESHOLD_3)					//check if there is an obstacle in front
			&& (IR7 >= PROX_THRESHOLD_3) && (IR3 >= PROX_THRESHOLD_3) && (IR6 >= PROX_THRESHOLD_3)){			//and on both sides.
		set_led(LED1,ON);
		set_led(LED3,ON);
		set_led(LED7,ON);
			set_robot_state(BYPASS_U_TURN);
	}
	if(((IR1 >= PROX_THRESHOLD_1) || (IR8 >= PROX_THRESHOLD_1)) && (IR2 <= PROX_THRESHOLD_3)
			&& (IR7 <= PROX_THRESHOLD_3) && (IR3 <= PROX_THRESHOLD_3) && (IR6 <= PROX_THRESHOLD_3)){			//check if there is an obstacle ONLY in front it.
		set_led(LED1, ON);																						//set the led where the obstacle is.
		set_robot_state(BYPASS_OBSTACLE_WALL);																	//switch thread in the main.
	}

	if(((IR1 >= PROX_THRESHOLD_1) || (IR8 >= PROX_THRESHOLD_1)) && (IR2 >= PROX_THRESHOLD_2)					//check if there is an obstacle in front
			&& (IR7 <= PROX_THRESHOLD_2) && (IR3 >= PROX_THRESHOLD_3) && (IR6 <= PROX_THRESHOLD_3)){			//and on the right.
		set_led(LED1, ON);
		set_led(LED3, ON);
		set_robot_state(BYPASS_OBSTACLE_ANGLE_RIGHT);
	}

	if(((IR1 >= PROX_THRESHOLD_1) || (IR8 >= PROX_THRESHOLD_1)) && (IR2 <= PROX_THRESHOLD_2)					//check if there is an obstacle in front
			&& (IR7 >= PROX_THRESHOLD_2) && (IR3 <= PROX_THRESHOLD_3) && (IR6 >= PROX_THRESHOLD_3)){			//and on the left.
		set_led(LED1, ON);
		set_led(LED7, ON);
		set_robot_state(BYPASS_OBSTACLE_ANGLE_LEFT);
	}

}

void wall_bypassing(void){								//When detect obstacle, turn on the right and the go straight forward while IR6 detect the wall.
	turn_90_right();
	clear_leds();
	while(IR6 >= PROX_THRESHOLD_3){
		go_straight_on();
	}													//If IR6 does not detect the wall then turn left and return to the main thread.
	chThdSleepMilliseconds(TIME_MARGIN);				//TIME_MARGIN prevents the robot from turning too quickly after the wall and colliding.
	turn_90_left();
	go_straight_on();
	set_robot_state(CRUISE_STATE);
}

void angle_right_bypassing(void){						//When detect obstacle, turn on the left and the go straight forward while IR3 detect the wall.
	turn_90_left();
	clear_leds();
	go_straight_on();
	while(IR3 >= PROX_THRESHOLD_3){
		go_straight_on();
	}
	chThdSleepMilliseconds(TIME_MARGIN);
	turn_90_right();
	go_straight_on();
	set_robot_state(CRUISE_STATE);
}

void angle_left_bypassing(void){						//When detect obstacle, turn on the right and the go straight forward while IR6 detect the wall.
	turn_90_right();
	clear_leds();
	go_straight_on();
	while(IR6 >= PROX_THRESHOLD_3){
		go_straight_on();
	}
	chThdSleepMilliseconds(TIME_MARGIN);
	turn_90_left();
	go_straight_on();
	set_robot_state(CRUISE_STATE);
}

void u_turn_bypassing(void){							//When detect obstacle, backtracking until the robot can turn on the left.
	while((IR2 >= PROX_THRESHOLD_BACK) && (IR7 >= PROX_THRESHOLD_BACK)){
		clear_leds();
		set_front_led(ON);
		backtracking();
	}
	set_front_led(OFF);
	turn_90_left();
	go_straight_on();
	set_robot_state(CRUISE_STATE);
}
