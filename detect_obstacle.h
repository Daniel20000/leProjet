/*
File : detect_obstacle.h
Author : Daniel Finell & Benoît Gallois
Date : 6 may 2022

Declarations of the functions that control the robot
*/


#ifndef DETECT_OBSTACLE_H
#define DETECT_OBSTACLE_H


/* Declaration of the MOTORS control functions . */
void go_straight_on(void);
void turn_90_left(void);
void turn_90_right(void);
void stop_robot(void);
void backtracking(void);


/* Declaration of the RGB_LED clear function. */
void clear_rgb_led(void);


/* Declaration of the different threads. */
void move_forward(void);
void wall_bypassing(void);
void angle_right_bypassing(void);
void angle_left_bypassing(void);
void u_turn_bypassing(void);
void steep_slope_warning(void);



//code clignoter toutes les leds rouges en quinconcent
//tout commenter et tout cleaner
//créer un troisième fichier pour la pente seulement?? peut etre utile



#endif /* DETECT_OBSTACLE_H */
