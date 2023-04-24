//
// Created by jackc on 2023/4/23.
//

#include "WalkAnimation.h"
#include "Resource.h"

static int counter = 0;

typedef struct {
    int currentFrameIndex;
    int direction; // 0 down 1 left 2 right 3 up
    int isMoving;
    SDL_Rect frames[16];
} WalkAnimationData;

static void WalkAnimation_OnDraw(DisplayObject *displayObject, SDL_Renderer *renderer) {
    auto *data = (WalkAnimationData *) displayObject->subClassData;
    if (data->currentFrameIndex > data->direction * 4 + 3) {
        data->currentFrameIndex = data->direction * 4;
    }
    SDL_RenderCopyF(
            renderer,
            Resource_GetWalkTexture(),
            &data->frames[data->currentFrameIndex],
            displayObject->dest
    );
    counter++;
    if (counter % 10 == 0) {
        counter = 0;
        if (data->isMoving) {
            data->currentFrameIndex++;
            data->isMoving = 0;
        } else {
            data->currentFrameIndex = data->direction * 4;
        }
    }
}

DisplayObject *WalkAnimation_Create() {
    auto *data = (WalkAnimationData *) malloc(sizeof(WalkAnimationData));
    data->currentFrameIndex = 0;
    data->direction = 0;
    data->isMoving = 0;
    for (int i = 0; i < 16; ++i) {
        data->frames[i].y = (i / 4) * 55;
        data->frames[i].x = (i % 4) * 54;
        data->frames[i].w = 54;
        data->frames[i].h = 55;
    }

    DisplayObject *obj = DisplayObject_Create(0, 0, 54, 55, WalkAnimation_OnDraw, nullptr);
    obj->subClassData = data;
    return obj;
}

void WalkAnimation_Moving(DisplayObject *self, SDL_Event *event, float maxW, float maxH) {
    auto *data = (WalkAnimationData *)self->subClassData;
    data->isMoving = 1;
    float step = 2;
    switch (event->key.keysym.sym) {
        case SDLK_DOWN:
            if (data->direction != 0) {
                data->direction = 0;
                data->currentFrameIndex = 0;
            } else {
                self->dest->y += step;
            }
            break;
        case SDLK_LEFT:
            if (data->direction != 1) {
                data->direction = 1;
                data->currentFrameIndex = 4;
            } else {
                self->dest->x -= step;
            }
            break;
        case SDLK_RIGHT:
            if (data->direction != 2) {
                data->direction = 2;
                data->currentFrameIndex = 8;
            } else {
                self->dest->x += step;
            }
            break;
        case SDLK_UP:
            if (data->direction != 3) {
                data->direction = 3;
                data->currentFrameIndex = 12;
            } else {
                self->dest->y -= step;
            }
            break;
        default:
            data->isMoving = 0;
            break;
    }
    if (self->dest->x < 0) {
        self->dest->x = 0;
    }
    if (self->dest->x > maxW - self->dest->w) {
        self->dest->x = maxW - self->dest->w;
    }
    if (self->dest->y < 0) {
        self->dest->y = 0;
    }
    if (self->dest->y > maxH - self->dest->h) {
        self->dest->y = maxH - self->dest->h;
    }
}

void WalkAnimation_Destroy(DisplayObject *self) {
    auto *data = (WalkAnimationData *) self->subClassData;
    free(data);
    DisplayObject_Destroy(self);
}
