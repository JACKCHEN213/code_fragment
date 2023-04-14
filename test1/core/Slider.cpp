//
// Created by jackc on 2023/4/17.
//

#include "Slider.h"

void Slider_DrawCallback(DisplayObject *displayObject, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRectF(renderer, displayObject->dest);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    auto *data = (SliderData *)displayObject->subClassData;
    SDL_RenderDrawRectF(renderer, data->sliderBarRect);
}

void Slider_MouseMoveCallback(DisplayObject *displayObject, SDL_Event *event) {
    auto *data = (SliderData *)displayObject->subClassData;
    data->sliderBarRect->x = (float)event->motion.x;
    if (data->sliderBarRect->x < displayObject->dest->x) {
        data->sliderBarRect->x = displayObject->dest->x;
    }
    if (data->sliderBarRect->x + data->sliderBarRect->w > displayObject->dest->x + displayObject->dest->w) {
        data->sliderBarRect->x = displayObject->dest->x + displayObject->dest->w - data->sliderBarRect->w;
    }
}

DisplayObject *Slider_Create(float x, float y, float w1, float h1, float w2, float h2) {
    DisplayObject *obj = DisplayObject_Create(x, y, w1, h1, Slider_DrawCallback, Slider_MouseMoveCallback);
    auto *data = (SliderData *) malloc(sizeof(SliderData));
    obj->subClassData = data;
    data->sliderBarRect = (SDL_FRect *) malloc(sizeof(SDL_FRect));
    data->sliderBarRect->x = x;
    data->sliderBarRect->y = y - (h2 / 4);
    data->sliderBarRect->w = w2;
    data->sliderBarRect->h = h2;
    return obj;

}

void Slider_Destroy(DisplayObject *self) {
    free(((SliderData *) self->subClassData)->sliderBarRect);
    free(self->subClassData);
    DisplayObject_Destroy(self);
}
