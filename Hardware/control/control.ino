#include "receiver.h"

void setup()
{
    Serial.begin(9600);

    log("Booting...");

    radio_setup();
    all_servo_startup();
    // all_touch_startup();
    all_led_startup();

    log("Boot Succesful");

    log("Running");
}

void loop()
{
    get_radio();
}