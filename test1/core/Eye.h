//
// Created by jackc on 2023/4/18.
//

#ifndef TEST1_EYE_H
#define TEST1_EYE_H


#include "DisplayObject.h"

typedef struct {
    float x;
    float y;
    float radius;
} EyeCircle;

DisplayObject *Eye_Create(float x, float y, float radius1, float radius2);

void Eye_Destroy(DisplayObject *self);


#endif //TEST1_EYE_H
