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
#include <sensors/proximity.h>

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




	//float time;
	int speedR=200;
	int speedL=200;
	int i=0;
	int b;



    /* Infinite loop. */
    while (1) {

    	right_motor_set_speed(speedR);
    	left_motor_set_speed(speedL);



    	//chprintf((BaseSequentialStream *)&SDU1, "%d ", b);


    	led_set_if_obstacle();




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


