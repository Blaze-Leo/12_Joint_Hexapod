#include "direction.h"

/////////////////////////////////
/////////////////////////////////
// CODE
/////////////////////////////////
/////////////////////////////////



void up_legs(int gait_id)
{   
    int *gait;
    if (gait_id==1)
    {gait = gait_A;}
    else if (gait_id ==2)
    {gait = gait_B;} 
    else
    {return;}

    int size = side_size;

    int delta[size];
    fill_array_int(delta,size,femur_delta_angle);

    servo_move_to_touch(gait, size, 2, delta, global_speed, false);
}


void down_legs(int gait_id)
{   
    int *gait;
    if (gait_id==1)
    {gait = gait_A;}
    else if (gait_id ==2)
    {gait = gait_B;} 
    else
    {return;}

    int size = side_size;

    int delta[size];
    fill_array_int(delta,size,-femur_delta_angle);
    
    servo_move_to_touch(gait, size, 2, delta, global_speed, false);
}

bool isInArray(int arr[], int size, int target) {

    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return true;
        }
    }
    return false;
}

void move_legs(int rotation_type, bool reverse)
{
    // rotation type 
    // 0 -- gA (default), gB (default)
    // 1 -- gA (inc), gB (dec)
    // 2 -- gA (dec), gB (dec)

    int *gait;
    gait = all_legs;

    int size = full_size;

    int delta_angle[size];
    fill_array_int(delta_angle,size,0);


    for (int i=0;i<size;i++)
    {
        bool check=isInArray(gait_A,side_size,i);
        if (reverse)
        {check=!check;}

        if (rotation_type == 0 )
        {
            delta_angle[i] = coxa_default_angle[i]-coxa_current_angle[i];
            continue;
        }
        else if (rotation_type == 2)
        {check=!check;}
        
        if (check)
        {
            delta_angle[i] = coxa_delta_angle;
        }
        else
        {
            delta_angle[i] = -coxa_delta_angle;
        }

    }

    servo_move_to_touch(gait, size, 1, delta_angle, global_speed, false);
}

void rotate_legs(int angle, int rotation_type)
{
    // rotation type 
    // 0 -- gA (default), gB (default)
    // 1 -- gA (inc), gB (dec)
    // 2 -- gA (dec), gB (dec)

    int *gait;
    gait = all_legs;

    int size = full_size;

    int end_angle[size];
    fill_array_int(end_angle,size,0);


    for (int i=0;i<size;i++)
    {
        bool check=isInArray(side_A,side_size,i);

        if (rotation_type == 0 )
        {
            end_angle[i] = coxa_default_angle[i]-coxa_current_angle[i];
            continue;
        }
        else if (rotation_type == 2)
        {check=!check;}
        
        if (check)
        {
            end_angle[i] = range_int(angle,coxa_delta_angle,-coxa_delta_angle);
        }
        else
        {
            end_angle[i] = range_int(-angle,coxa_delta_angle,-coxa_delta_angle);
        }

    }

    servo_move_to_touch(gait, size, 1, end_angle, global_speed, false);
}


void move_base(bool move, bool reverse)
{
    int pos = gait_counter;

    if (pos == 1)
    {pos = 2;}
    else if (pos == 2)
    {pos = 1;}

    up_legs(pos);

    if (move)
    {move_legs(pos,reverse);}
    else
    {move_legs(0,reverse);}

    down_legs(pos);

    if (move)
    {gait_counter=pos;}
    else
    {gait_counter=0;}
}

void rotate_base(int angle, bool side)
{
    angle = stabilize_angle(angle);

    int d1=0;
    int d2=0;

    if(side)
    {d1=1;d2=2;}
    else
    {d1=2;d2=1;}

    up_legs(d1);
    rotate_legs(angle,d1);
    down_legs(d1);

    up_legs(d2);
    rotate_legs(angle,d2);
    down_legs(d2);
}


void base_height(int angle)
{
    angle = stabilize_angle(angle);

    int *gait;
    gait = all_legs;

    int size = full_size;

    int delta_angle[size];
    fill_array_int(delta_angle,size,range_int(angle,femur_delta_angle,-femur_delta_angle));

    servo_move_to_touch(gait, size, 2, delta_angle, global_speed, false);

    reset_default_angles();
}

void base_yaw(int angle)
{
    angle = stabilize_angle(angle);

    int *gait;
    gait = all_legs;

    int size = full_size;

    int delta_angle[size];
    fill_array_int(delta_angle,size,range_int(angle,coxa_delta_angle,-coxa_delta_angle));

    servo_move_to_touch(gait, size, 1, delta_angle, global_speed, false);

    reset_default_angles();
}

void base_roll(int angle, bool side)
{
    angle = stabilize_angle(angle);

    int *gait;
    gait = all_legs;

    int size = full_size;

    int delta_angle[size];
    fill_array_int(delta_angle,size,0);


    for (int i=0;i<size;i++)
    {
        bool check=isInArray(side_A,side_size,i);

        if (side)
        {check=!check;}

        if (check)
        {
            delta_angle[i] = range_int(-angle,femur_delta_angle,-femur_delta_angle);
        }
        else
        {
            delta_angle[i] = range_int(angle,femur_delta_angle,-femur_delta_angle);
        }

    }

    servo_move_to_touch(gait, size, 2, delta_angle, global_speed, false);

    reset_default_angles();
}

void base_pitch(int angle, bool side)
{
    angle = stabilize_angle(angle);
    
    int *gait;
    gait = all_legs;

    int size = full_size;

    int delta_angle[size];
    fill_array_int(delta_angle,size,0);

    for (int i=0;i<size;i++)
    {
        bool check=isInArray(front_legs,pair_size,i);

        bool is_middle = isInArray(middle_legs,pair_size,i);

        if (side)
        {check=!check;}

        if ((!is_middle) && check)
        {
            delta_angle[i] = range_int(-angle,femur_delta_angle,-femur_delta_angle);
        }
        else if (!is_middle)
        {
            delta_angle[i] = range_int(angle,femur_delta_angle,-femur_delta_angle);
        }

    }

    servo_move_to_touch(gait, size, 2, delta_angle, global_speed, false);

    reset_default_angles();
}

void org_reset()
{
    int size=full_size;

    int *gait;
    gait = all_legs;

    int delta1[size];
    fill_array_int(delta1,size,0);

    int delta2[size];
    fill_array_int(delta2,size,0);

    for(int i=0;i<size;i++)
    {
        delta1[i]=stabilize_angle(coxa_current_angle[i]-coxa_org_angle[i]);
        delta2[i]=stabilize_angle(femur_current_angle[i]-femur_org_angle[i]);
    }

    servo_move_to_touch(gait, size, 1, delta1, global_speed, false);
    servo_move_to_touch(gait, size, 2, delta2, global_speed, false);

    reset_default_angles();
}

void default_reset()
{
    int size=full_size;

    int *gait;
    gait = all_legs;

    int delta1[size];
    fill_array_int(delta1,size,0);

    int delta2[size];
    fill_array_int(delta2,size,0);

    for(int i=0;i<size;i++)
    {
        delta1[i]=stabilize_angle(coxa_current_angle[i]-coxa_default_angle[i]);
        delta2[i]=stabilize_angle(femur_current_angle[i]-femur_default_angle[i]);
    }

    servo_move_to_touch(gait, size, 1, delta1, global_speed, false);
    servo_move_to_touch(gait, size, 2, delta2, global_speed, false);

    reset_default_angles();
}

void reset_default_angles()
{
    int size = full_size;

    for(int i=0;i<size;i++)
    {
        coxa_default_angle[i]=coxa_current_angle[i];
        femur_default_angle[i]=femur_current_angle[i];
    }

    reset_delta_angles();
}

void reset_delta_angles()
{
    int size = full_size;

    int up = 0;
    int down = 0;

    int delta[size];
    fill_array_int(delta,size,0);


    for (int i = 0; i< size; i++)
    {
        up=coxa_max_angle[i]-coxa_default_angle[i];
        down=coxa_default_angle[i]-coxa_min_angle[i];

        delta[i]=minimum_int(up,down);
    }

    int delta_angle=delta[0];

    for(int i=0;i<size;i++)
    {
        if (delta[i]<delta_angle)
        {delta_angle=delta[i];}
    }

    coxa_delta_angle=delta_angle;

    //////////////////////

    for (int i = 0; i< size; i++)
    {
        up=femur_max_angle[i]-femur_default_angle[i];
        down=femur_default_angle[i]-femur_min_angle[i];

        delta[i]=minimum_int(up,down);
    }

    delta_angle=delta[0];

    for(int i=0;i<size;i++)
    {
        if (delta[i]<delta_angle)
        {delta_angle=delta[i];}
    }

    femur_delta_angle=delta_angle;
} 