/////////////////////////////////
/////////////////////////////////
/////////////////////////////////

#ifndef MOVEMENT_H
#define MOVEMENT_H

/////////////////////////////////
/////////////////////////////////
// HEADER FILE
/////////////////////////////////
/////////////////////////////////

#include "variable.h"

int stabilize_angle(int angle);

void servo_setup(Servo &servo_obj, int servo_pin);
void button_setup(int button_pin);
void led_setup(int button_pin);
bool check_button(int button_pin);

void all_servo_startup();
void all_touch_startup();
void all_led_startup();

int minimum_int(int a,int b);
int maximum_int(int a,int b);
int range_int(int a, int max, int min);

void individual_servo(int leg_id, int leg_type, int delta, int speed);
void servo_move_to_touch(int leg_id[], int size, int leg_type, int delta[], int speed,bool until_touch);

/////////////////////////////////
/////////////////////////////////
/////////////////////////////////

#endif