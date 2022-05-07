/*
File : detect_obstacle.h
Author : Daniel Finell & Benoît Gallois
Date : 6 may 2022
Declarations of the functions that control the robot.
*/

#ifndef DETECT_OBSTACLE_H
#define DETECT_OBSTACLE_H


/* Defines the LED states. */
#define OFF						0
#define ON						1


/* Defines the threshold for the IMU. */
#define SLOPE_THRESHOLD			5750


/* Declaration of the MOTORS control functions . */
void go_straight_on(void);
void turn_90_left(void);
void turn_90_right(void);
void stop_robot(void);
void backtracking(void);


/* Declaration of the different threads. */
void move_forward(void);
void wall_bypassing(void);
void angle_right_bypassing(void);
void angle_left_bypassing(void);
void u_turn_bypassing(void);


#endif /* DETECT_OBSTACLE_H */
