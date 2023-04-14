//
// Created by jackc on 2023/4/14.
//

#ifndef TEST1_CURSOR_H
#define TEST1_CURSOR_H

#include <SDL2/SDL.h>
#include "DisplayObject.h"

DisplayObject *Cursor_Create(float x, float y, float w, float h);

void Cursor_Destroy(DisplayObject *self);

#endif //TEST1_CURSOR_H
