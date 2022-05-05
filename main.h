#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "camera/dcmi_camera.h"
#include "msgbus/messagebus.h"
#include "parameter/parameter.h"

#define CRUISE_STATE					0
#define BYPASS_OBSTACLE_WALL			1
#define BYPASS_OBSTACLE_ANGLE_RIGHT		2
#define BYPASS_OBSTACLE_ANGLE_LEFT		3
#define BYPASS_U_TURN					4
#define CAUTION_STEEP_SLOPE				5

void set_robot_state(uint8_t new_state);



/** Robot wide IPC bus. */
extern messagebus_t bus;

extern parameter_namespace_t parameter_root;

void SendUint8ToComputer(uint8_t* data, uint16_t size);

#ifdef __cplusplus
}
#endif

#endif

