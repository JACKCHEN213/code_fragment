//
// Created by jackc on 2023/4/6.
//

#include "Resource.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture *texture;

int Resource_Load(SDL_Renderer *renderer, const char *filename) {
    texture = IMG_LoadTexture(renderer, filename);
    if (texture == nullptr) {
        SDL_Log("Failed to load resource, %s", SDL_GetError());
        return 1;
    }
    return 0;
}

SDL_Texture *Resource_GetTexture() {
    return texture;
}

void Resource_Unload() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}
