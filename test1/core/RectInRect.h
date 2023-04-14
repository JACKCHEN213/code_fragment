//
// Created by jackc on 2023/4/17.
//

#ifndef TEST1_RECTINRECT_H
#define TEST1_RECTINRECT_H


#include "DisplayObject.h"

typedef struct {
    SDL_FRect *rectInRectBarRect;
} RectInRectData;


DisplayObject *RectInRect_Create(float x, float y, float w1, float h1, float w2, float h2);

void RectInRect_Destroy(DisplayObject *self);


#endif //TEST1_RECTINRECT_H
