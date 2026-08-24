#include "ValloxDecoder.h"

void ValloxDecoder::decode(uint8_t frame[6]) {

    uint8_t variable = frame[3];
    uint8_t value    = frame[4];

    switch(variable) {

        case 0x32:
            Serial.print("OUTDOOR AIR TEMPERATURE: ");
            Serial.println(value, HEX);
            break;

        case 0x33:
            Serial.print("EXHAUST AIR TEMPERATURE: ");
            Serial.println(value, HEX);
            break;

        case 0x34:
            Serial.print("EXTRACT AIR TEMPERATURE: ");
            Serial.println(value, HEX);
            break;

        case 0x35:
            Serial.print("SUPPLY AIR TEMPERATURE: ");
            Serial.println(value, HEX);
            break;
    }
}
