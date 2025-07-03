#include "receiver.h"

/////////////////////////////////
/////////////////////////////////
// CODE
/////////////////////////////////
/////////////////////////////////

void radio_setup()
{
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_LOW);
    radio.startListening();
}

void get_radio()
{

    if (radio.available())
    {
        radio.read(&data_packet, sizeof(data_packet));
    }
    
    int packet_length=25;

    for (int i=0; i<packet_length;i++)
    {
        int command = i ;
        int arguments = data_packet.args[i];

        execute_command(command,arguments);
    }
}

void respond(int args)
{
    if (args==1)
    {
        digitalWrite(respond_led,HIGH);
        delay(2000);
        digitalWrite(respond_led,LOW);
    }
}

void execute_command(int command,int args)
{
    ////////////////
    // command and args chart
    ////////////////
    // 0  --> respond         -- true
    // 1  --> coxa_1_angle    -- angle
    // 2  --> coxa_2_angle    -- angle
    // 3  --> coxa_3_angle    -- angle
    // 4  --> coxa_4_angle    -- angle
    // 5  --> coxa_5_angle    -- angle
    // 6  --> coxa_6_angle    -- angle
    // 7  --> femur_1_angle   -- angle
    // 8  --> femur_2_angle   -- angle
    // 9  --> femur_3_angle   -- angle
    // 10 --> femur_4_angle   -- angle
    // 11 --> femur_5_angle   -- angle
    // 12 --> femur_6_angle   -- angle
    // 13 --> up_leg         -- gait_id
    // 14 --> down_leg       -- gait_id
    // 15 --> global_movement -- reverse
    // 16 --> global_rotate   -- side
    // 17 --> move_base      -- stable
    // 18 --> rotate_base    -- angle
    // 19 --> base_height    -- height
    // 20 --> base_yaw       -- angle
    // 21 --> base_roll      -- angle
    // 22 --> base_pitch     -- angle
    // 23 --> org_reset      -- true
    // 24 --> default_reset  -- true
    
    switch(command) 
    {
        case 0:
            respond(args);
            break;

        case 1:
            individual_servo(0,1,args,global_speed);
            break;
        case 2:
            individual_servo(1,1,args,global_speed);
            break;
        case 3:
            individual_servo(2,1,args,global_speed);
            break;
        case 4:
            individual_servo(3,1,args,global_speed);
            break;
        case 5:
            individual_servo(4,1,args,global_speed);
            break;
        case 6:
            individual_servo(5,1,args,global_speed);
            break;

        case 7:
            individual_servo(0,2,args,global_speed);
            break;
        case 8:
            individual_servo(1,2,args,global_speed);
            break;
        case 9:
            individual_servo(2,2,args,global_speed);
            break;
        case 10:
            individual_servo(3,2,args,global_speed);
            break;
        case 11:
            individual_servo(4,2,args,global_speed);
            break;
        case 12:
            individual_servo(5,2,args,global_speed);
            break;

        case 13:
            up_legs(args);
            break;
        case 14:
            down_legs(args);
            break;

        case 15:
            if (args==0)
            {global_reverse=false;}
            if (args==1)
            {global_reverse=true;}
            break;
        case 16:
            if (args==0)
            {global_rotate_side=false;}
            if (args==1)
            {global_rotate_side=true;}
            break;

        case 17:
            if (args==0)
            {move_base(false,global_reverse);}
            if (args==1)
            {move_base(true,global_reverse);}
            break;
            
        case 18:
            rotate_base(args,global_rotate_side);
            break;

        case 19:
            base_height(args);
            break;
        case 20:
            base_yaw(args);
            break;
        case 21:
            base_roll(args,global_rotate_side);
            break;
        case 22:
            base_pitch(args,global_rotate_side);
            break;

        case 23:
            if (args==1)
            {org_reset();}
            break;

        case 24:
            if (args==1)
            {default_reset();}
            break;

        default:
            // handle unknown
            break;
    }

}
