/*
File : steep_slope.h
Author : Daniel Finell & Benoît Gallois
Date : 6 may 2022
Declaration of function if a steep slope is detected.
*/


#ifndef STEEP_SLOPE_H
#define STEEP_SLOPE_H


void clear_rgb_led(void);
void toggle_led(led_name_t led_number);


void check_slope(void);
void steep_slope_warning(void);


#endif /* STEEP_SLOPE_H */
