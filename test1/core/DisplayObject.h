//
// Created by jackc on 2023/4/14.
//

#ifndef TEST1_DISPLAYOBJECT_H
#define TEST1_DISPLAYOBJECT_H

#include <SDL2/SDL.h>

typedef struct DisplayObject {
    SDL_FRect *dest;
    void *subClassData;

    void (*onDraw)(struct DisplayObject *displayObject, SDL_Renderer *renderer);

    void (*onMouseMove)(struct DisplayObject *displayObject, SDL_Event *event);
} DisplayObject;


typedef void(*DisplayObjectOnDrawCallback)(struct DisplayObject *displayObject, SDL_Renderer *renderer);

typedef void(*DisplayObjectOnMouseMoveCallback)(struct DisplayObject *displayObject, SDL_Event *event);


DisplayObject *DisplayObject_Create(
        float_t x, float y, float w, float h,
        DisplayObjectOnDrawCallback onDrawCallback,
        DisplayObjectOnMouseMoveCallback onMouseMoveCallback);

void DisplayObject_Draw(DisplayObject *self, SDL_Renderer *renderer);

void DisplayObject_OnMouseMove(DisplayObject *self, SDL_Event *event);

void DisplayObject_Destroy(DisplayObject *self);


#endif //TEST1_DISPLAYOBJECT_H
