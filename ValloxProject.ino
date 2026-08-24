#include <HardwareSerial.h>
#include "ValloxDecoder.h"

HardwareSerial RS485(2);
ValloxDecoder decoder;

void setup() {

    Serial.begin(115200);

    RS485.begin(
        9600,
        SERIAL_8N1,
        4,
        5
    );
}

void loop() {

    if (RS485.available() >= 6) {

        uint8_t frame[6];

        for(int i = 0; i < 6; i++) {
            frame[i] = RS485.read();
        }

        decoder.decode(frame);
    }
}
