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

//liste de tous nos define
#define CRUISING_SPEED         1000
#define STOP_SPEED             0
#define TURN_SPEED			   500



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


//Ce code fonctionne ilm faut mnt changer les noms des capteurs IR
void led_set_if_obstacle(void)  //si un capteur infrarouge de 1,3,5,7 capte un obstacle alors la led respective s'allume
{
	while(get_prox(0) >= 100 || get_prox(7) >= 100)
	{
		set_led(LED1, 1);
	}
	while(get_prox(2) >= 100)
	{
		set_led(LED3, 1);
	}
	while(get_prox(3) >= 100 || get_prox(4) >= 100)
	{
		set_led(LED5, 1);
	}
	while(get_prox(5) >= 100)
	{
		set_led(LED7, 1);
	}
	clear_leds();
}




void eviter_obstacle(void)   //Attention speed doit etre negatif pour reculer
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
{
	int j;
	int16_t res;
	while(j!=3)
	{
		res = get_gyro(j);
			if(res >= 90)
			{
				toggle_rgb_led(LED2, GREEN_LED, RGB_MAX_INTENSITY);
				toggle_rgb_led(LED4, GREEN_LED, RGB_MAX_INTENSITY);
				toggle_rgb_led(LED6, GREEN_LED, RGB_MAX_INTENSITY);
				toggle_rgb_led(LED8, GREEN_LED, RGB_MAX_INTENSITY);
			}
		j=j+1;
	}
}
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


