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

uint8_t state_of_robot=0;

static THD_WORKING_AREA(waObstacle, 128);
static THD_FUNCTION(Obstacle, arg) {

    chRegSetThreadName(__FUNCTION__);
    (void)arg;

    

    while(1){
        switch(state_of_robot){
            case CRUISE_STATE:
                move_forward();
                break;
            case BYPASS_OBSTACLE_1:
                obstacle_1_bypassing();
                break;
            case BYPASS_OBSTACLE_2:
                obstacle_2_bypassing();
                break;
            case BYPASS_U_TURN:
                u_turn_bypassing();
                break;

            chThdSleepMilliseconds(500);
        }
    }
}

static THD_WORKING_AREA(waPente, 128);
static THD_FUNCTION(Pente, arg) {

    chRegSetThreadName(__FUNCTION__);
    (void)arg;

    while(1){
        switch(state_of_robot){        
                case CAUTION_STEEP_SLOPE:
                steep_slope_warning();
                break;

        chThdSleepMilliseconds(500);

        }
    }
}


int main(void)
{
	//SystemClock_Config();
    halInit();
    chSysInit();

    messagebus_init(&bus, &bus_lock, &bus_condvar);

    /*
     * Initalisation Proximity Sensor
     */
    proximity_start();
    calibrate_ir();

    /*
     * Initialisation IMU
     */
    imu_start();
    calibrate_acc();

    usb_start();

    /*
     * Initialisation motors
     */
	motors_init();


chThdCreateStatic(waObstacle, sizeof(waObstacle), NORMALPRIO, Obstacle, NULL);
chThdCreateStatic(waPente, sizeof(waPente), NORMALPRIO, Pente, NULL);

}
    	
#define STACK_CHK_GUARD 0xe2dee396
uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

void __stack_chk_fail(void)
{
    chSysHalt("Stack smashing detected");
}