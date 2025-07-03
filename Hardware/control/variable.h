/////////////////////////////////
/////////////////////////////////
/////////////////////////////////

#ifndef VARIABLE_H
#define VARIABLE_H

/////////////////////////////////
/////////////////////////////////
// HEADER FILE
/////////////////////////////////
/////////////////////////////////

#include "Arduino.h"
#include "stdint.h"
#include "ESP32Servo.h"
#include "SPI.h"
#include "nRF24L01.h"
#include "RF24.h"

extern int respond_led;

extern int coxa_servo_pin[6];

extern int coxa_delta_angle;
extern int coxa_min_angle[6];
extern int coxa_max_angle[6];
extern int coxa_org_angle[6];
extern int coxa_default_angle[6];
extern int coxa_current_angle[6];

extern int femur_servo_pin[6];

extern int femur_delta_angle;
extern int femur_min_angle[6];
extern int femur_max_angle[6];
extern int femur_org_angle[6];
extern int femur_default_angle[6];
extern int femur_current_angle[6];

extern int foot_touch_pin[6];

extern int global_speed;

extern bool global_reverse;
extern bool global_rotate_side;

extern int gait_A[3];
extern int gait_B[3];

extern int side_A[3];
extern int side_B[3];

extern int front_legs[2];
extern int middle_legs[2];
extern int back_legs[2];

extern int full_size;
extern int side_size;
extern int pair_size;

extern int all_legs[6];

extern int gait_counter;

extern Servo coxa_servo_objects[6];
extern Servo femur_servo_objects[6];


extern int radio_ce;
extern int radio_csn;

extern const byte address[6];

extern RF24 radio;

struct DataPacket {
    int8_t args[25];
};

extern DataPacket data_packet;

void log(const char* message);

void fill_array_int(int arr[], int size, int value);
void fill_array_bool(bool arr[], int size, bool value);

/////////////////////////////////
/////////////////////////////////
/////////////////////////////////

#endif