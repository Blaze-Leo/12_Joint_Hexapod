#include "SPI.h"
#include "nRF24L01.h"
#include "RF24.h"
#include "stdint.h"

int ce_pin=0;
int csn_pin=0;

RF24 radio(ce_pin,csn_pin);  // CE, CSN
const byte address[6] = "12345";

int8_t data_packet[25];  // global

void serial_receive() {
  if (Serial.available() >= 25) {
    for (int i = 0; i < 25; i++) {
      int8_t val = (int8_t)(Serial.read());
      data_packet[i] = val;  // store in global
    }
  }
}

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}

void loop() {
  serial_receive();
  send_packet();
}


void send_packet() {

  bool success = radio.write(&data_packet, sizeof(data_packet));
  if (success) {
    Serial.println("Send - OK");
  } else {
    Serial.println("Send - FAILED");
  }

  delay(100);
}

