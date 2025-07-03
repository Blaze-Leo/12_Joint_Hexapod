#include "movement.h"

/////////////////////////////////
/////////////////////////////////
// CODE
/////////////////////////////////
/////////////////////////////////

int stabilize_angle(int angle)
{
    if (angle>0)
    {angle=angle%360;}
    
    if (angle<0)
    {angle=-((-angle)%360);}

    if (angle>180)
    {angle=-(360-angle);}

    if (angle<-180)
    {angle=(360+angle);}

    if (angle<0 || angle>180)
    {log("Incorect Angle sent for Stablizing");}
    // {log("Incorect Angle sent for Stablizing");angle = constrain(angle, 0, 180);}

    return angle;
}

void servo_setup(Servo &servo_obj, int servo_pin)
{
    servo_obj.attach(servo_pin);
}

void button_setup(int button_pin)
{
    // 5V to pin

    pinMode(button_pin, INPUT);
}

void all_servo_startup()
{
    int size=full_size;

    for(int i=0;i<size;i++)
    {
        servo_setup(coxa_servo_objects[i],coxa_servo_pin[i]);
        servo_setup(femur_servo_objects[i],femur_servo_pin[i]);
    }
}

void all_touch_startup()
{
    int size=full_size;

    for(int i=0;i<size;i++)
    {
        button_setup(foot_touch_pin[i]);
    }
}

void led_setup(int button_pin)
{

    pinMode(button_pin, OUTPUT);
}

void all_led_startup()
{
    led_setup(respond_led);
}

bool check_button(int button_pin)
{
    int press = digitalRead(button_pin);

    return press==HIGH;
}

void individual_servo(int leg_id, int leg_type, int delta, int speed)
{
    int leg[1]={leg_id};
    int delta_angles[1]={delta};

    servo_move_to_touch(leg,1,leg_type,delta_angles,speed,false);
}

int minimum_int(int a,int b)
{
    return (a<b)?a:b;
}

int maximum_int(int a,int b)
{
    return (a>b)?a:b;
}

int range_int(int a, int max, int min)
{
    if (a>max)
    {a=max;}
    if (a<min)
    {a=min;}

    return a;
}

void servo_move_to_touch(int leg_id[], int size, int leg_type, int delta[], int speed,bool until_touch)
{
    // gloabl_speed is in deg/sec

    int delay_value = int(1000 / speed);

    bool done[size];
    fill_array_bool(done,size,false);

    int step[size];
    fill_array_int(step,size,0);

    int pos[size];
    fill_array_int(pos,size,0);

    int end[size];
    fill_array_int(end,size,0);

    Servo* servo_obj[size];

    for (int i=0;i<size;i++)
    {   
        int start_angle=0;
        int end_angle=0;

        if (leg_type==1)
        {
            servo_obj[i] = &coxa_servo_objects[leg_id[i]];
            start_angle = coxa_current_angle[leg_id[i]];
            end_angle = start_angle+delta[i];
            end_angle = range_int(end_angle,coxa_max_angle[leg_id[i]],coxa_min_angle[leg_id[i]]);
        }

        else if (leg_type==2)
        {
            servo_obj[i] = &femur_servo_objects[leg_id[i]];
            start_angle = femur_current_angle[leg_id[i]];
            end_angle = start_angle+delta[i];
            end_angle = range_int(end_angle,femur_max_angle[leg_id[i]],femur_min_angle[leg_id[i]]);
        }

        pos[i]=stabilize_angle(start_angle);
        end[i]=stabilize_angle(end_angle);


        if (start_angle < end[i])
        {
            step[i] = 1;
        }
        else if (start_angle > end[i])
        {
            step[i] = -1;
        }
    }

    bool all_done=false;

    while(!all_done)
    {
        
        for (int i=0;i<size;i++)
        {   
            if (until_touch)
            {
                if (check_button(foot_touch_pin[leg_id[i]]))
                {
                    end[i]=pos[i];
                }
            }

            if (pos[i]==end[i])
            {
                done[i]=true;
            }
            else
            {
                pos[i]+=step[i];
            }

            servo_obj[i]->write(pos[i]);
        }

        delay(delay_value);

        all_done=true;
        for (int i=0;i<size;i++)
        {
            all_done=all_done && done[i];
        }
    }

    for (int i=0;i<size;i++)
    {
        if (leg_type==1)
        {
            coxa_current_angle[leg_id[i]]=pos[i];
        }

        else if (leg_type==2)
        {
            femur_current_angle[leg_id[i]]=pos[i];
        }
    }
}

