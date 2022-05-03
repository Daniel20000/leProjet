static THD_WORKING_AREA(waObstacle, 128);
static THD_FUNCTION(Obstacle, arg) {

    chRegSetThreadName(__FUNCTION__);
    (void)arg;

    

    while(1){
        switch(state_of_robot){
            case CRUISE_STATE:
                move_forward();
                break;
            case BYPASS_OBSTACLE_1:
                obstacle_1_bypassing();
                break;
            case BYPASS_OBSTACLE_2:
                obstacle_2_bypassing();
                break;
            case BYPASS_U_TURN:
                u_turn_bypassing();
                break;

            chThdSleepMilliseconds(500);
        }
    }
}

static THD_WORKING_AREA(waPente, 128);
static THD_FUNCTION(Pente, arg) {

    chRegSetThreadName(__FUNCTION__);
    (void)arg;

    while(1){
        
                case CAUTION_STEEP_SLOPE:
                steep_slope_warning();
                break;

        chThdSleepMilliseconds(500);

    
    }
}


//Dans le main() avant la boucle while(1)
chThdCreateStatic(waObstacle, sizeof(waObstacle), NORMALPRIO, Obstacle, NULL);
chThdCreateStatic(waPente, sizeof(waPente), NORMALPRIO, Pente, NULL);