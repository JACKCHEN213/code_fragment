//
// Created by jackc on 2023/4/14.
//

#include "Cursor.h"
#include "Resource.h"

static void Cursor_OnDraw(DisplayObject *self, SDL_Renderer *renderer) {
    SDL_RenderCopyF(renderer, Resource_GetCursorTexture(), nullptr, self->dest);
}

static void Cursor_OnMouseMove(DisplayObject *self, SDL_Event *event) {
    self->dest->x = (float)event->motion.x;
    self->dest->y = (float)event->motion.y;
}

DisplayObject *Cursor_Create(float x, float y, float w, float h) {
    return DisplayObject_Create(x, y, w, h, Cursor_OnDraw, Cursor_OnMouseMove);
}

void Cursor_Destroy(DisplayObject *self) {
    DisplayObject_Destroy(self);
}
