//
// Created by jackc on 2023/4/11.
//
#include <cstdint>
#include <cstdlib>
#include <random>
#include <ctime>

std::random_device rd;
std::default_random_engine gen = std::default_random_engine(rd());
std::uniform_int_distribution<int> dis(0, 255);
std::uniform_int_distribution<int> dis2(128, 255);


uint32_t getARGB()
{
    uint32_t a = dis2(gen) << 24;
    uint32_t r = dis(gen) << 16;
    uint32_t g = dis(gen) << 8;
    uint32_t b = dis(gen);
    uint32_t color = a | r | g | b;
    return color;
}
