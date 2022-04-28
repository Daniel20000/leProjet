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
void led_set_if_obstacle(led_name_t led_number, int IR_1, int IR_3, int IR_5, int IR_7)  //si un capteur infrarouge de 1,3,5,7 capte un obstacle alors la led respective s'allume
{
	switch(led_number)
	{
		case LED1:
			if(IR_1 == 1)
			{
				set_led(LED1, 1);
			} else
			{
				break;
			}
			break;
		case LED3:
			if(IR_3 == 1)
			{
				set_led(LED3, 1);
			} else
			{
				break;
			}
			break;
		case LED5:
			if(IR_5 == 1)
			{
				set_led(LED5, 1);
			} else
			{
				break;
			}
			break;
		case LED7:
			if(IR_7 == 1)
			{
				set_led(LED7, 1);
			} else
			{
				break;
			}
			break;
		default:
			for(int i=0; i<4; i++)
			{
				clear_leds();
			}
	}
}




void eviter_obstacle(int sped, int i)   //Attention speed doit etre negatif pour reculer
{
	if(i > 3)  //si le capteur IR3 capte un objet alors les moteurs reculent et puis tourne sur eux meme et réavance pour éviter l'obstacle
	{
		while(i > 3)  // tant que le capteur capte l'objet il continue de reculer
		{
			right_motor_set_speed(sped);
			left_motor_set_speed(sped);
		}
	}
	i = i+1;
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


