//
// Created by jackc on 2023/4/23.
//

#ifndef TEST1_WALKANIMATION_H
#define TEST1_WALKANIMATION_H

#include "DisplayObject.h"

DisplayObject *WalkAnimation_Create();

void WalkAnimation_Moving(DisplayObject *self, SDL_Event *event, float maxW, float maxH);

void WalkAnimation_Destroy(DisplayObject *self);


#endif //TEST1_WALKANIMATION_H
