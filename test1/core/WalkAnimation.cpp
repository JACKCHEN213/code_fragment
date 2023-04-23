//
// Created by jackc on 2023/4/23.
//

#include "WalkAnimation.h"
#include "Resource.h"

static int counter = 0;

typedef struct {
    int currentFrameIndex;
    SDL_Rect frames[16];
} WalkAnimationData;

static void WalkAnimation_OnDraw(DisplayObject *displayObject, SDL_Renderer *renderer) {
    auto *data = (WalkAnimationData *) displayObject->subClassData;
    if (data->currentFrameIndex > 15) {
        data->currentFrameIndex = 0;
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
        data->currentFrameIndex++;
    }
}

DisplayObject *WalkAnimation_Create() {
    auto *data = (WalkAnimationData *) malloc(sizeof(WalkAnimationData));
    data->currentFrameIndex = 3;
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

void WalkAnimation_Destroy(DisplayObject *self) {
    auto *data = (WalkAnimationData *) self->subClassData;
    free(data);
    DisplayObject_Destroy(self);
}
