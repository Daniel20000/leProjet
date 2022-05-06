/*
File : detect_obstacle.h
Author : Daniel Finell & Benoît Gallois
Date : 6 may 2022
Declarations of the functions that control the robot.
*/


#ifndef DETECT_OBSTACLE_H
#define DETECT_OBSTACLE_H


/* Defines the IR sensors name. */
#define IR1         		 	get_prox(0)
#define IR2           			get_prox(1)
#define IR3			   			get_prox(2)
#define IR4         		 	get_prox(3)
#define IR5           			get_prox(4)
#define IR6			   			get_prox(5)
#define IR7         		 	get_prox(6)
#define IR8           			get_prox(7)


/* Defines the LED states. */
#define OFF						0
#define ON						1


/* Defines the acceleration axis. */
#define X						get_acc(0)
#define Y						get_acc(1)


/* Defines the thresholds for the IR sensors and IMU. */
#define PROX_THRESHOLD			100
#define PROX_UTURN_TRESH		100
#define SLOPE_THRESHOLD			5000


/* Defines the time constants.*/
#define TIME_TO_TURN			1075
#define TIME_MARGIN				250


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



//code clignoter toutes les leds rouges en quinconcent
//tout commenter et tout cleaner
//créer un troisième fichier pour la pente seulement?? peut etre utile



#endif /* DETECT_OBSTACLE_H */
