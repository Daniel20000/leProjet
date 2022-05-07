/*
File : steep_slope.h
Author : Daniel Finell & Benoît Gallois
Date : 6 may 2022
Declaration of function if a steep slope is detected.
*/

#ifndef STEEP_SLOPE_H
#define STEEP_SLOPE_H


/* Declaration of the LEDs control functions . */
void set_all_rgb_led(uint8_t red_val, uint8_t green_val, uint8_t blue_val);
void clear_all_rgb_led(void);
void set_all_led(uint8_t value);


/* Declaration of the slope detection and warning functions . */
void check_slope(void);
void steep_slope_warning(void);


#endif /* STEEP_SLOPE_H */
