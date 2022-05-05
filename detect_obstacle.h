#ifndef DETECT_OBSTACLE_H
#define DETECT_OBSTACLE_H

//start the PI regulator thread

void go_straight_on(void);
void turn_90_left(void);
void turn_90_right(void);
void stop_robot(void);
void backtracking(void);

void clear_rgb_led(void);

void move_forward(void);
void wall_bypassing(void);
void angle_right_bypassing(void);
void angle_left_bypassing(void);
void u_turn_bypassing(void);
void steep_slope_warning(void);



//rajouter les conditions dans les fonctions pour détecter constement si la pente est trop grande
//tout commenter et tout cleaner
//créer un troisième fichier pour la pente seulement



#endif /* DETECT_OBSTACLE_H */
