#include "variable.h"

/////////////////////////////////
/////////////////////////////////
// CODE
/////////////////////////////////
/////////////////////////////////

int respond_led=0;

int coxa_servo_pin[6] = {0,0,0,0,0,0};

int coxa_delta_angle= 0 ;
// maximum plus minus angle 

int coxa_min_angle[6] = {45,45,45,45,45,45};
int coxa_max_angle[6] = {135,135,135,135,135,135};
int coxa_org_angle[6] = {90,90,90,90,90,90};
int coxa_default_angle[6] = {90,90,90,90,90,90};
int coxa_current_angle[6] = {90,90,90,90,90,90};

int femur_servo_pin[6] = {0,0,0,0,0,0};

int femur_delta_angle = 0;
// maximum plus minus angle 

int femur_min_angle[6] = {45,45,45,45,45,45};
int femur_max_angle[6] = {135,135,135,135,135,135};
int femur_org_angle[6] = {90,90,90,90,90,90};
int femur_default_angle[6] = {90,90,90,90,90,90};
int femur_current_angle[6] = {90,90,90,90,90,90};

int foot_touch_pin[6] = {0,0,0,0,0,0};

int global_speed = 100;

bool global_reverse=false;
bool global_rotate_side=false;

int gait_A[3] = {0,2,4};
int gait_B[3] = {1,3,5};

int side_A[3] = {0,5,4};
int side_B[3] = {1,2,3};

int front_legs[2] = {0,1};
int middle_legs[2] = {2,5};
int back_legs[2] = {3,4};

int full_size=6;
int side_size=3;
int pair_size=2;

int all_legs[6] = {0,1,2,3,4,5};

int gait_counter = 0;

Servo coxa_servo_objects[6];
Servo femur_servo_objects[6];

// gait 1 --> 1,3,5
// gait 2 --> 2,4,6

int radio_ce = 0;
int radio_csn = 0;

const byte address[6] = "12345";

RF24 radio(radio_ce,radio_csn);

DataPacket data_packet;

void log(const char* message) {
    Serial.print("[LOG] ");
    Serial.println(message);
}

void fill_array_int(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        arr[i] = value;
    }
}

void fill_array_bool(bool arr[], int size, bool value) {
    for (int i = 0; i < size; i++) {
        arr[i] = value;
    }
}


