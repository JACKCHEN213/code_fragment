//
// Created by jackc on 2023/4/18.
//

#ifndef TEST1_CIRCLE_H
#define TEST1_CIRCLE_H

#include <SDL2/SDL.h>
#include "point.h"

void DrawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius) {
    const int32_t diameter = (radius * 2);
    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);
    while (x >= y) {
        //  Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);
        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }
        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void FillCircle(SDL_Renderer *renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

/**
 * 获取过圆心的射线在圆上的坐标
 * 1. m / n = (y2 - y1) / (x2 - x1); m^2 + n^2 = r^2
 * 2. n^2 = r^2 / (((y2 - y2) / (x2 - x1))^2 + 1)
 * 3. m^2 = r^2 - n^2
 * 4. IF (x2 > x1 && y2 > y1) THEN (x1 + n, y1 + m)
 * 5. ELIF (x2 > x1 && y2 < y1) THEN (x1 + n, y1 - m)
 * 6. ELIF (x2 < x1 && y2 > y1) THEN (x1 - n, y1 + m)
 * 7. ELIF (x2 < x1 && y2 M y1) THEN (x1 - n, y1 - m)
 * @param x1
 * @param y1
 * @param r
 * @param x2
 * @param y2
 * @return
 */
SDL_FPoint GetIntersectionPointOfLine(float x1, float y1, float r, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float n = SDL_sqrtf(SDL_powf(r, 2) / (SDL_powf((dy / dx), 2) + 1));
    float m = SDL_sqrtf(SDL_powf(r, 2) - SDL_powf(n, 2));
    SDL_FPoint point;
    if (x2 > x1) {
        point.x = x1 + n;
    } else {
        point.x = x1 - n;
    }
    if (y2 > y1) {
        point.y = y1 + m;
    } else {
        point.y = y1 - m;
    }
    return point;
}

/**
 * 判断点是否在园内
 * @param x1
 * @param y1
 * @param r
 * @param x2
 * @param y2
 * @return
 */
SDL_bool JudgePointInCircle(float x1, float y1, float r, float x2, float y2) {
    float distance = GetPointDistance(x1, y1, x2, y2);
    if (r > distance) {
        return SDL_TRUE;
    }
    return SDL_FALSE;
}

#endif //TEST1_CIRCLE_H
