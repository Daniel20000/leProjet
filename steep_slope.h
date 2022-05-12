/*
File : steep_slope.h
Author : Daniel Finell & Benoît Gallois
Date : 12 may 2022
Declaration of function if a steep slope is detected.
*/

#ifndef STEEP_SLOPE_H
#define STEEP_SLOPE_H


/* Declaration of the LEDs control functions . */

/**
 * @brief   Switch on all the RGB led 2,4,6,8 in same time
 *
 * @param red_val, green_val, blue_val     0-100, OFF - RGB_MAX_INTENSITY.
 *
 */
void set_all_rgb_led(uint8_t red_val, uint8_t green_val, uint8_t blue_val);

/**
 * @brief   Switch off all the RGB led in same time.
 */
void clear_all_rgb_led(void);

/**
 * @brief   Switch on/off all the led 1,3,5,7 in same time
 *
 * @param value     0-1, respectively OFF-ON.
 *
 */
void set_all_led(uint8_t value);



/* Declaration of the slope detection and warning functions . */

/**
 * @brief   Check if the acceleration of the X and Y axis exceed the stall value.
 */
void check_slope(void);

/**
 * @brief   As long as the slope is too steep, the robot remains in safety mode.
 *			It stops then the RGB_LED blink in blue then the red LED then the BODY_LED simultaneously.
 */
void steep_slope_warning(void);


#endif /* STEEP_SLOPE_H */
