//
// Created by jackc on 2023/4/19.
//

#ifndef TEST1_POINT_H
#define TEST1_POINT_H
#include <SDL2/SDL.h>

/**
 * 求两点之间的距离
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @return
 */
float GetPointDistance(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float distance = SDL_sqrtf(SDL_powf(dx, 2) + SDL_powf(dy, 2));
    return distance;
}

#endif //TEST1_POINT_H
