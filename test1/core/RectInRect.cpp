//
// Created by jackc on 2023/4/17.
//

#include "RectInRect.h"
void RectInRect_DrawCallback(DisplayObject *displayObject, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRectF(renderer, displayObject->dest);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    auto *data = (RectInRectData *)displayObject->subClassData;
    SDL_RenderDrawRectF(renderer, data->rectInRectBarRect);
}

void RectInRect_MouseMoveCallback(DisplayObject *displayObject, SDL_Event *event) {
    auto *data = (RectInRectData *)displayObject->subClassData;
    data->rectInRectBarRect->x = (float)event->motion.x;
    if (data->rectInRectBarRect->x < displayObject->dest->x) {
        data->rectInRectBarRect->x = displayObject->dest->x;
    }
    if (data->rectInRectBarRect->x + data->rectInRectBarRect->w > displayObject->dest->x + displayObject->dest->w) {
        data->rectInRectBarRect->x = displayObject->dest->x + displayObject->dest->w - data->rectInRectBarRect->w;
    }

    data->rectInRectBarRect->y = (float)event->motion.y;
    if (data->rectInRectBarRect->y < displayObject->dest->y) {
        data->rectInRectBarRect->y = displayObject->dest->y;
    }
    if (data->rectInRectBarRect->y + data->rectInRectBarRect->h > displayObject->dest->y + displayObject->dest->h) {
        data->rectInRectBarRect->y = displayObject->dest->y + displayObject->dest->h - data->rectInRectBarRect->h;
    }
}

DisplayObject *RectInRect_Create(float x, float y, float w1, float h1, float w2, float h2) {
    DisplayObject *obj = DisplayObject_Create(x, y, w1, h1, RectInRect_DrawCallback, RectInRect_MouseMoveCallback);
    auto *data = (RectInRectData *) malloc(sizeof(RectInRectData));
    obj->subClassData = data;
    data->rectInRectBarRect = (SDL_FRect *) malloc(sizeof(SDL_FRect));
    data->rectInRectBarRect->x = x;
    data->rectInRectBarRect->y = y - (h2 / 4);
    data->rectInRectBarRect->w = w2;
    data->rectInRectBarRect->h = h2;
    return obj;

}

void RectInRect_Destroy(DisplayObject *self) {
    free(((RectInRectData *) self->subClassData)->rectInRectBarRect);
    free(self->subClassData);
    DisplayObject_Destroy(self);
}
