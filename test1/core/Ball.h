//
// Created by jackc on 2023/4/6.
//

#ifndef TEST1_BALL_H
#define TEST1_BALL_H

#include <SDL2\SDL.h>

typedef struct {
    SDL_Rect dest;
    double angle;
    double rotateSpeed;
} Ball;

Ball *Ball_Create(int x, int y, double rotateSpeed);

void Ball_Draw(Ball *self, SDL_Renderer *renderer);

void Ball_Destroy(Ball *ball);

#endif //TEST1_BALL_H
