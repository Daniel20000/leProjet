#include "spi_comm.h"
#include <leds.h>
#define RGB_MIN_INTENSITY 0

spi_comm_start();



//void ledplay () {

    //LED2 toggle
    void set_rgb_led(rgb_led_name_t LED2, uint8_t RGB_MAX_INTENSITY, uint8_t RGB_MAX_INTENSITY, uint8_t RGB_MIN_INTENSITY);
    chThdSleepMilliseconds(1000); //waits 1 second
    void set_rgb_led(rgb_led_name_t LED2, uint8_t RGB_MIN_INTENSITY, uint8_t RGB_MIN_INTENSITY, uint8_t RGB_MIN_INTENSITY);
    chThdSleepMilliseconds(1000); //waits 1 second
    
    //LED4 toggle
    void set_rgb_led(rgb_led_name_t LED4, uint8_t RGB_MAX_INTENSITY, uint8_t RGB_MAX_INTENSITY, uint8_t RGB_MIN_INTENSITY);
    chThdSleepMilliseconds(1000); //waits 1 second
    void set_rgb_led(rgb_led_name_t LED4, uint8_t RGB_MIN_INTENSITY, uint8_t RGB_MIN_INTENSITY, uint8_t RGB_MIN_INTENSITY);
    chThdSleepMilliseconds(1000); //waits 1 second
    
    //LED6 toggle
    void set_rgb_led(rgb_led_name_t LED6, uint8_t RGB_MAX_INTENSITY, uint8_t RGB_MAX_INTENSITY, uint8_t RGB_MIN_INTENSITY);
    chThdSleepMilliseconds(1000); //waits 1 second
    void set_rgb_led(rgb_led_name_t LED6, uint8_t RGB_MIN_INTENSITY, uint8_t RGB_MIN_INTENSITY, uint8_t RGB_MIN_INTENSITY);
    chThdSleepMilliseconds(1000); //waits 1 second


//}