//
// Created by jackc on 2023/4/6.
//

#ifndef TEST1_RESOURCE_H
#define TEST1_RESOURCE_H

#include <SDL2/SDL.h>


int Resource_Load(SDL_Renderer *renderer, const char *filename);

SDL_Texture *Resource_GetTexture();

SDL_Surface *Resource_GetSurface();

SDL_Cursor *Resource_GetCursor();

SDL_Texture *Resource_GetCursorTexture();

void Resource_Unload();


#endif //TEST1_RESOURCE_H
