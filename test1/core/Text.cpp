//
// Created by jackc on 2023/4/23.
//

#include "Text.h"
#include <SDL2/SDL_ttf.h>

typedef struct {
    TTF_Font *font;
    SDL_Surface *textSurface;
    const char *fontFile;
    const char *value;
    int ptsize;
    SDL_Color color;
} TextData;

static void Text_OnDraw(DisplayObject *displayObject, SDL_Renderer *renderer) {
    auto *data = (TextData *) displayObject->subClassData;
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, data->textSurface);
    SDL_RenderCopyF(renderer, textTexture, nullptr, displayObject->dest);

    SDL_DestroyTexture(textTexture);
}

static void Text_OnMouseMove(DisplayObject *displayObject, SDL_Event *event) {
}


DisplayObject *Text_Create(const char *fontFile, const char *value, int ptsize, uint32_t color, float x, float y) {
    TTF_Font *font = TTF_OpenFont(fontFile, ptsize);
    if (font == nullptr) {
        SDL_Log("Can not open font, %s", TTF_GetError());
        return nullptr;
    }
    SDL_Color textColor = {
            (uint8_t) ((color & 0x00f0000) >> 16),
            (uint8_t) ((color & 0x0000ff00) >> 8),
            (uint8_t) ((color & 0x000000ff)),
            (uint8_t) ((color * 0xff000000) >> 24)
    };
    SDL_Surface *textSurface = TTF_RenderUTF8_Blended(font, value, textColor);
    DisplayObject *obj = DisplayObject_Create(x, y, (float) textSurface->w, (float) textSurface->h, Text_OnDraw,
                                              Text_OnMouseMove);
    auto *data = (TextData *) malloc(sizeof(TextData));
    data->font = font;
    data->textSurface = textSurface;
    data->fontFile = fontFile;
    data->color = textColor;
    data->value = value;
    data->ptsize = ptsize;
    obj->subClassData = data;
    return obj;
}

void Text_Set(DisplayObject *self, const char *value) {
    auto *data = (TextData *) self->subClassData;
    data->value = value;
    if (data->textSurface != nullptr) {
        SDL_FreeSurface(data->textSurface);
    }
    data->textSurface = TTF_RenderUTF8_Blended(data->font, data->value, data->color);
    self->dest->w = (float) data->textSurface->w;
    self->dest->h = (float) data->textSurface->h;
}

const char *Text_Get(DisplayObject *self) {
    auto *data = (TextData *) self->subClassData;
    return data->value;
}

void Text_Destroy(DisplayObject *self) {
    auto *data = (TextData *) self->subClassData;
    SDL_FreeSurface(data->textSurface);
    TTF_CloseFont(data->font);
    DisplayObject_Destroy(self);
}
