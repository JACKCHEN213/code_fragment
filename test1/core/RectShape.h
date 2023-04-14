//
// Created by jackc on 2023/4/11.
//

#ifndef TEST1_RECTSHAPE_H
#define TEST1_RECTSHAPE_H

#include <SDL2/SDL.h>


typedef struct RectShape {
    SDL_FRect dest;
    uint32_t color;
    float _offsetX;
    float _offsetY;
    int _dragEnabled;
    struct RectShape *prev;
    struct RectShape *next;
} RectShape;

RectShape *RectShape_Create(float x, float y, float w, float h, uint32_t color);

void RectShape_Draw(RectShape *self, SDL_Renderer *renderer);

SDL_bool RectShape_OnMouseEvent(RectShape *self, SDL_Event *event);

void RectShape_Destroy(RectShape *self);


#endif //TEST1_RECTSHAPE_H
