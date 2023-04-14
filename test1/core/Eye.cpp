//
// Created by jackc on 2023/4/18.
//

#include "Eye.h"
#include "../utils/circle.h"

static void Eye_DrawCallback(DisplayObject *displayObject, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    DrawCircle(
            renderer,
            (int32_t) (displayObject->dest->x + displayObject->dest->w),
            (int32_t) (displayObject->dest->y + displayObject->dest->w),
            (int32_t) displayObject->dest->w);
    auto *subCircle = (EyeCircle *) displayObject->subClassData;
    FillCircle(renderer,
               (int32_t) (subCircle->x + subCircle->radius * 1.5),
               (int32_t) (subCircle->y + subCircle->radius * 1.5),
               (int32_t) subCircle->radius);
}

static void Eye_MouseMoveCallBack(DisplayObject *displayObject, SDL_Event *event) {
    auto *subCircle = (EyeCircle *) displayObject->subClassData;
    subCircle->x = (float) event->motion.x - subCircle->radius;
    subCircle->y = (float) event->motion.y - subCircle->radius;
    // 判断点是否在园内
    SDL_bool isInCircle = JudgePointInCircle(
            displayObject->dest->x + displayObject->dest->w,
            displayObject->dest->y + displayObject->dest->w,
            displayObject->dest->w,
            subCircle->x + subCircle->radius,
            subCircle->y + subCircle->radius);
    if (isInCircle == SDL_FALSE) {
        SDL_FPoint point = GetIntersectionPointOfLine(
                displayObject->dest->x + displayObject->dest->w / 2,
                displayObject->dest->y + displayObject->dest->w / 2,
                displayObject->dest->w,
                subCircle->x + subCircle->radius,
                subCircle->y + subCircle->radius);
        subCircle->x = point.x;
        subCircle->y = point.y;
    }
}


DisplayObject *Eye_Create(float x, float y, float radius1, float radius2) {
    DisplayObject *obj = DisplayObject_Create(x, y, radius1, radius1, Eye_DrawCallback, Eye_MouseMoveCallBack);
    auto *circle = (EyeCircle *) malloc(sizeof(EyeCircle));
    circle->x = x;
    circle->y = y;
    circle->radius = radius2;
    obj->subClassData = circle;
    return obj;
}

void Eye_Destroy(DisplayObject *self) {
    free(self->subClassData);
    DisplayObject_Destroy(self);
}