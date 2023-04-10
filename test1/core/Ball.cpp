//
// Created by jackc on 2023/4/6.
//
#include "Ball.h"
#include "Resource.h"

Ball *Ball_Create(int x, int y, double rotateSpeed) {
    Ball *ball = (Ball *)malloc(sizeof(Ball));
    ball->dest = {x, y, 60, 60};
    ball->angle = 0;
    ball->rotateSpeed = rotateSpeed;
    return ball;
}

void Ball_Draw(Ball *self, SDL_Renderer *renderer) {
    self->angle += self->rotateSpeed;
    SDL_RenderCopyEx(
            renderer,
            Resource_GetTexture(),
            nullptr,
            &self->dest,
            self->angle,
            nullptr,
            SDL_FLIP_NONE);
}

void Ball_Destroy(Ball *ball) {
    free(ball);
}
