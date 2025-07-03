/////////////////////////////////
/////////////////////////////////
/////////////////////////////////

#ifndef DIRECTION_H
#define DIRECTION_H

/////////////////////////////////
/////////////////////////////////
// HEADER FILE
/////////////////////////////////
/////////////////////////////////

#include "movement.h"

bool isInArray(int arr[], int size, int target);

void up_legs(int gait_id);
void down_legs(int gait_id);

void move_legs(int rotation_type, bool reverse);
void rotate_legs(int delta_angle, int rotation_type);

void move_base(bool stable, bool reverse);
void rotate_base(int angle, bool side);

void base_height(int angle);
void base_yaw(int angle);
void base_roll(int angle, bool side);
void base_pitch(int angle, bool side);

void org_reset();
void default_reset();

void reset_default_angles();
void reset_delta_angles();

/////////////////////////////////
/////////////////////////////////
/////////////////////////////////

#endif
