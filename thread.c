static THD_WORKING_AREA(waBlinker, 128);
static THD_FUNCTION(Blinker, arg) {
 
  while (true) {
	led_set_if_obstacle(LED7, 0, 0, 0, 1);
	chThdSleepMilliseconds(500);
  }
}

/*
 *  Starts the thread Blinker in the main.c 
 */
void blinker_start(void){
	chThdCreateStatic(waBlinker, sizeof(waBlinker), NORMALPRIO, Blinker, NULL);
}

//appel dans le main:
blinker_start();