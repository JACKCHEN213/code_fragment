//
// Created by jackc on 2023/4/14.
//

#include "DisplayObject.h"

DisplayObject *DisplayObject_Create(
        float_t x, float y, float w, float h,
        DisplayObjectOnDrawCallback onDrawCallback,
        DisplayObjectOnMouseMoveCallback onMouseMoveCallback) {
    auto *obj = (DisplayObject *) malloc(sizeof(DisplayObject));
    obj->dest = (SDL_FRect *)malloc(sizeof(SDL_FRect));
    obj->dest->x = x;
    obj->dest->y = y;
    obj->dest->w = w;
    obj->dest->h = h;
    obj->onDraw = onDrawCallback;
    obj->onMouseMove = onMouseMoveCallback;
    obj->subClassData = nullptr;
    return obj;
}

void DisplayObject_Draw(DisplayObject *self, SDL_Renderer *renderer) {
    if (self->onDraw != nullptr) {
        self->onDraw(self, renderer);
    }
}

void DisplayObject_OnMouseMove(DisplayObject *self, SDL_Event *event) {
    if (self->onMouseMove != nullptr) {
        self->onMouseMove(self, event);
    }
}

void DisplayObject_Destroy(DisplayObject *self) {
    free(self->dest);
    free(self);
}