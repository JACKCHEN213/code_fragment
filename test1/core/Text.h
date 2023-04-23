//
// Created by jackc on 2023/4/23.
//

#ifndef TEST1_TEXT_H
#define TEST1_TEXT_H


#include "DisplayObject.h"

DisplayObject *Text_Create(const char *fontFile, const char *value, int ptsize, uint32_t color, float x, float y);

void Text_Set(DisplayObject *self, const char *value);

const char *Text_Get(DisplayObject *self);

void Text_Destroy(DisplayObject *self);


#endif //TEST1_TEXT_H
