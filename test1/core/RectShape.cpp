//
// Created by jackc on 2023/4/11.
//

#include "RectShape.h"

RectShape *RectShape_Create(float x, float y, float w, float h, uint32_t color) {
    auto *self = (RectShape *) malloc(sizeof(RectShape));
    self->color = color;
    self->dest.x = x;
    self->dest.y = y;
    self->dest.w = w;
    self->dest.h = h;
    self->_dragEnabled = 0;
    return self;
}

void RectShape_Draw(RectShape *self, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(
            renderer,
            (self->color & 0x00ff0000) >> 16,
            (self->color & 0x0000ff00) >> 8,
            (self->color & 0x000000ff),
            (self->color & 0xff000000) >> 24
    );
    SDL_RenderFillRectF(renderer, &self->dest);
}

SDL_bool RectShape_OnMouseEvent(RectShape *self, SDL_Event *event) {
    switch (event->type) {
        case SDL_MOUSEMOTION:
            if (self->_dragEnabled) {
                self->dest.x = (float)event->motion.x - self->_offsetX;
                self->dest.y = (float)event->motion.y - self->_offsetY;
                return SDL_TRUE;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if ((float)event->button.x < self->dest.x || (float)event->button.x > self->dest.x + self->dest.w) {
                break;
            }
            if ((float)event->button.y < self->dest.y || (float)event->button.y > self->dest.y + self->dest.h) {
                break;
            }
            self->_offsetX = (float)event->button.x - self->dest.x;
            self->_offsetY = (float)event->button.y - self->dest.y;
            self->_dragEnabled = 1;
            return SDL_TRUE;
        case SDL_MOUSEBUTTONUP:
            if ((float)event->button.x < self->dest.x || (float)event->button.x > self->dest.x + self->dest.w) {
                break;
            }
            if ((float)event->button.y < self->dest.y || (float)event->button.y > self->dest.y + self->dest.h) {
                break;
            }
            self->_dragEnabled = 0;
            return SDL_TRUE;
    }
    return SDL_FALSE;
}

void RectShape_Destroy(RectShape *self) {
    free(self);
}
