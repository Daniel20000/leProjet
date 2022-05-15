/*
File : detect_obstacle.h
Author : Daniel Finell & Benoît Gallois
Date : 12 may 2022
Declarations of the functions that control the robot.
*/

#ifndef DETECT_OBSTACLE_H
#define DETECT_OBSTACLE_H


/* Defines the LED states. */
#define OFF						0
#define ON						1


/* Declaration of the MOTORS control functions . */
void go_straight_on(void);
void turn_90_left(void);
void turn_90_right(void);
void stop_robot(void);
void backtracking(void);


/* Declaration of the different threads. */

/**
 * @brief   The robot goes ahead.
 * 			And check if there is an obstacle (dead end, wall in front, 90° wall on right/left).
 */
void move_forward(void);

/**
 * @brief   Turns on the LED 1,3,7 to show that it has detected the obstacle.
 * 			It moves backwards as long as it detects that it is surrounded by the side walls.
 * 			Lights on the front led when it moves backwards.
 */
void u_turn_bypassing(void);

/**
 * @brief   Turns on the led 1 to show that it has detected the obstacle.
 * 			Turns to the right and continues straight ahead as long as it detects the wall on its left.
 * 			Once the wall is passed, it returns to the left.
 */
void wall_bypassing(void);

/**
 * @brief   Turns on the led 1 and 3 to show that it has detected the obstacle.
 *			Turns to the left and continues straight on as long as it detects the wall on its right.
 *			Once the wall is passed, it returns to the right.
 */
void angle_right_bypassing(void);

/**
 * @brief   Same as the the angle_right_bypassing() function, but on the contrary.
 */
void angle_left_bypassing(void);



#endif /* DETECT_OBSTACLE_H */
