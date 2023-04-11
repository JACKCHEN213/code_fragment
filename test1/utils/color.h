//
// Created by jackc on 2023/4/11.
//
#include <stdint.h>
#include <stdlib.h>

uint32_t getARGB()
{
    uint32_t a = (rand() % 128 + 127) << 24;
    uint32_t r = (rand() % 255) << 16;
    uint32_t g = (rand() % 255) << 8;
    uint32_t b = rand() % 255;
    uint32_t color = a | r | g | b;
    return color;
}
