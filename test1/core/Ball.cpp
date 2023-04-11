//
// Created by jackc on 2023/4/6.
//
#include "Ball.h"
#include "Resource.h"

Ball *Ball_Create(float x, float y, double rotateSpeed, float speedX, float speedY) {
    Ball *ball = (Ball *)malloc(sizeof(Ball));
    ball->dest = {x, y, 60, 60};
    ball->angle = 0;
    ball->rotateSpeed = rotateSpeed;
    ball->speedX = speedX;
    ball->speedY = speedY;
    return ball;
}

void Ball_Draw(Ball *self, SDL_Renderer *renderer) {
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    self->angle += self->rotateSpeed;
    self->dest.x += self->speedX;
    if (self->dest.x > (float)w - self->dest.w ||  self->dest.x < 0) {
        self->speedX = -self->speedX;
    }
    self->dest.y += self->speedY;
    if (self->dest.y > (float)h  - self->dest.h ||  self->dest.y < 0) {
        self->speedY = -self->speedY;
    }

    SDL_RenderCopyExF(
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
