#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ch.h"
#include "hal.h"
#include "memory_protection.h"
#include <usbcfg.h>
#include <main.h>
#include <motors.h>
#include <chprintf.h>
#include <leds.h>
#include <sensors/proximity.h>
#include <sensors/imu.h>
#include <pi_regulator.h>


//definition of the usual speed
#define CRUISING_SPEED          200
#define STOP_SPEED              0
#define TURN_SPEED			    300

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
#define Z						get_acc(2)	  		//normalement pas utilisé

//definition of threshhold
#define SLOPE_THRESHOLD				2500
#define PROX_THRESHOLD				10
#define TURN_MARGING				3



extern int state_of_robot;



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
}

void turn_90_right(void){
	right_motor_set_speed(STOP_SPEED);
	left_motor_set_speed(TURN_SPEED);
}

void stop_robot(void){
	right_motor_set_speed(STOP_SPEED);
	left_motor_set_speed(STOP_SPEED);
}

void backtracking(void){
	right_motor_set_speed(- CRUISING_SPEED);
	left_motor_set_speed(- CRUISING_SPEED);
}


/*
 * Definition des fonctions principales
 */

void move_forward(void){
	go_straight_on();
	if(IR1 >=  PROX_THRESHOLD|| IR8 >= PROX_THRESHOLD){
		chprintf((BaseSequentialStream *)&SDU1, "%d ", IR1);
		//set_led(LED1, ON);
		state_of_robot = BYPASS_OBSTACLE;
	}
	/*
	if((IR1 >= PROX_THRESHOLD || IR8 >= PROX_THRESHOLD) && (IR6 >= PROX_THRESHOLD) && (IR3 >= PROX_THRESHOLD)){
		set_led(LED1,ON);
		set_led(LED3,ON);
		set_led(LED7,ON);
		state_of_robot = BYPASS_U_TURN;
	}
	*/
	/*if(X > SLOPE_THRESHOLD || X < -SLOPE_THRESHOLD){
		state_of_robot = CAUTION_STEEP_SLOPE;
	}*/
}


void obstacle_bypassing(void){
	while(IR6 <= (PROX_THRESHOLD+TURN_MARGING)){
		turn_90_right();
	}
	while(IR6 >= (PROX_THRESHOLD)){
		go_straight_on();
	}

	//POUR LES VIRAGES UTILISER DES TIMERS ET PAS DES WHILE (TROP IMPRESCIS)

	/*
	while(IR6 <= (PROX_THRESHOLD+TURN_MARGING)){
		turn_90_left();
	}
	*/
	state_of_robot = CRUISE_STATE;
}

void u_turn_bypassing(void){
	backtracking();
}

void steep_slope_warning(void){
	set_front_led(ON);
}

