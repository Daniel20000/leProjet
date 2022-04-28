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
#include <camera/po8030.h>
#include <chprintf.h>
#include <leds.h>
#include <sensors/imu.h>

#include <detect_obstacle.h>

messagebus_t bus;
MUTEX_DECL(bus_lock);
CONDVAR_DECL(bus_condvar);

void SendUint8ToComputer(uint8_t* data, uint16_t size) 
{
	chSequentialStreamWrite((BaseSequentialStream *)&SD3, (uint8_t*)"START", 5);
	chSequentialStreamWrite((BaseSequentialStream *)&SD3, (uint8_t*)&size, sizeof(uint16_t));
	chSequentialStreamWrite((BaseSequentialStream *)&SD3, (uint8_t*)data, size);
}


int main(void)
{
	//SystemClock_Config();
    halInit();
    chSysInit();

    messagebus_init(&bus, &bus_lock, &bus_condvar);

    //Il faut qu'on initialise un mutexe pour pouvoir l'utiliser
    proximity_start();
    calibrate_ir();


    //start IMU
    imu_start();



    usb_start();

    //inits the motors
	motors_init();

	//init gyroscope
	//imu_start();    Besoin d'un mutex pour l gyro aussi
	//calibrate_gyro();

	//float time;
	int speedR=1000;
	int speedL=1000;
	int i=0;




    /* Infinite loop. */
    while (1) {

    	int16_t a;
    	a = get_acc_filtered(0, 20);

    	chprintf((BaseSequentialStream *)&SDU1, a);


    	/* PARTIE GYROSCOPE
    	int j;
    	int16_t res;
    	while(j!=3)
    	{
    		res = get_gyro(j);
    		if(res >= 1)
    		{
    			toggle_rgb_led(LED2, GREEN_LED, RGB_MAX_INTENSITY);
    			toggle_rgb_led(LED4, GREEN_LED, RGB_MAX_INTENSITY);
    			toggle_rgb_led(LED6, GREEN_LED, RGB_MAX_INTENSITY);
    			toggle_rgb_led(LED8, GREEN_LED, RGB_MAX_INTENSITY);
    		}
    		j=j+1;
    	}
		*/

    	right_motor_set_speed(speedR);
    	left_motor_set_speed(speedL);

    	//chprintf((BaseSequentialStream *)&SDU1, "Hello world");

    	//CODE POUR LE CAPTEUR DE POSITION QUI FAIT RECULER LE ROBOT POUR LE CONTOURNER
    	if(i>3 && i<10)  //si le capteur IR3 capte un objet alors les moteurs reculent et puis tourne sur eux meme et réavance pour éviter l'obstacle
    		{
    			speedR = 0;
    			speedL = 575;

    			while(i>3 && i<10)  // tant que le capteur capte l'objet il continue de reculer
    			{
    				led_set_if_obstacle(LED1, 1, 0, 0, 0);

    				right_motor_set_speed(speedR);
    				left_motor_set_speed(speedL);
    				i = i+1;
    			}
    		}


    	if(i>=12 && i<19)  //si le capteur IR3 capte un objet alors les moteurs reculent et puis tourne sur eux meme et réavance pour éviter l'obstacle
    	    		{
    	    			speedR = 575;
    	    			speedL = 0;

    	    			while(i>=10 && i<17)  // tant que le capteur capte l'objet il continue de reculer
    	    			{
    	    				led_set_if_obstacle(LED7, 0, 0, 0, 1);

    	    				right_motor_set_speed(speedR);
    	    				left_motor_set_speed(speedL);
    	    				i = i+1;
    	    			}
    	    		}


    	i = i+1;
    	speedR = 1000;
    	speedL = 1000;



    	//100Hz
    	//chThdSleepUntilWindowed(time, time + MS2ST(10));
        chThdSleepMilliseconds(1000); //waits 1 second
    }
}

#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}


