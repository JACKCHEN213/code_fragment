//
// Created by jackc on 2023/4/17.
//

#ifndef TEST1_SLIDER_H
#define TEST1_SLIDER_H


#include "DisplayObject.h"

typedef struct {
    SDL_FRect *sliderBarRect;
} SliderData;


DisplayObject *Slider_Create(float x, float y, float w1, float h1, float w2, float h2);

void Slider_Destroy(DisplayObject *self);


#endif //TEST1_SLIDER_H
