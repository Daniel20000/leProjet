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

//definition of steep slopes
#define SLOPE_MAX				1000

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
	toggle_rgb_led(LED4, GREEN_LED, RGB_MAX_INTENSITY);
	toggle_rgb_led(LED6, GREEN_LED, RGB_MAX_INTENSITY);
}


void move_forward(void){
	go_straight_on();
	if(IR1 >= 160 || IR8 >= 160){
		set_led(LED1, ON);
		state_of_robot = BYPASS_OBSTACLE;
	}
	if((IR1 >= 160 || IR8 >= 160) && (IR6 >= 160) && (IR3 >= 160)){
		set_led(LED1,ON);
		set_led(LED3,ON);
		set_led(LED7,ON);
		state_of_robot = BYPASS_U_TURN;
	}
	if(X > SLOPE_MAX || X < -SLOPE_MAX){
		state_of_robot = CAUTION_STEEP_SLOPE;
	}
}


void obstacle_bypassing(void){
	stop_robot();
}

void u_turn_bypassing(void){
	backtracking();
}

void steep_slope_warning(void){
	set_front_led(ON);
}










void led_set_if_obstacle(void)  //si un capteur infrarouge de 1,3,5,7 capte un obstacle alors la led respective s'allume
{
	if(get_prox(0) >= 100 || get_prox(7) >= 100)
	{
		set_led(LED1, 1);
	}
	if(get_prox(2) >= 100)
	{
		set_led(LED3, 1);
	}
	if(get_prox(3) >= 100 || get_prox(4) >= 100)
	{
		set_led(LED5, 1);
	}
	if(get_prox(5) >= 100)
	{
		set_led(LED7, 1);
	}
	clear_leds();
}


void eviter_obstacle(void)
{
	if(get_prox(0)>=40)
	{
		if(get_prox(5)<=30)
		{
			turn_90_right();
		}
		if(get_prox(5)>=30)
		{
			go_straight_on();
		}
	}
}


/*
void detection_pente_forte(void)
*/














/*
static THD_WORKING_AREA(waBlinker, 128);
static THD_FUNCTION(Blinker, arg) {

  while (true) {
	led_set_if_obstacle(LED1, 1, 0, 0, 0);
	chThdSleepMilliseconds(500);
  }
}
*/
