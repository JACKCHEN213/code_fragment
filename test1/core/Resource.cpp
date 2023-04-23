//
// Created by jackc on 2023/4/6.
//

#include "Resource.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static SDL_Texture *texture;
static SDL_Surface *cursorSurface;
static SDL_Cursor *cursor;
static SDL_Texture *cursorTexture;
static SDL_Texture *walkTexture;

int Resource_Load(SDL_Renderer *renderer, const char *filename) {
    texture = IMG_LoadTexture(renderer, filename);
    if (texture == nullptr) {
        SDL_Log("Failed to load resource, %s", SDL_GetError());
        return 1;
    }
    cursorSurface = IMG_Load("img/cursor_2.png");
    if (cursorSurface == nullptr) {
        SDL_Log("Failed to load resource, %s", SDL_GetError());
        return 1;
    }
    walkTexture = IMG_LoadTexture(renderer, "img/walk.png");
    if (walkTexture == nullptr) {
        SDL_Log("Failed to load resource, %s", SDL_GetError());
        return 1;
    }
    cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);
    cursorTexture = SDL_CreateTextureFromSurface(renderer, cursorSurface);
    return 0;
}

SDL_Texture *Resource_GetTexture() {
    return texture;
}

SDL_Surface *Resource_GetSurface() {
    return cursorSurface;
}

SDL_Cursor *Resource_GetCursor() {
    return cursor;
}

SDL_Texture *Resource_GetCursorTexture() {
    return cursorTexture;
}

SDL_Texture *Resource_GetWalkTexture() {
    return walkTexture;
}

void Resource_Unload() {
    if (walkTexture != nullptr) {
        SDL_DestroyTexture(walkTexture);
    }
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
    if (cursor != nullptr) {
        SDL_FreeCursor(cursor);
    }
    if (cursorSurface != nullptr) {
        SDL_FreeSurface(cursorSurface);
    }
    if (cursorTexture != nullptr) {
        SDL_DestroyTexture(cursorTexture);
    }
}
