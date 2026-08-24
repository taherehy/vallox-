#ifndef VALLOX_DECODER_H
#define VALLOX_DECODER_H

#include <Arduino.h>

class ValloxDecoder {
public:
    void decode(uint8_t frame[6]);
};

#endif
