#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#undef main
#define WIDTH 400
#define HEIGHT 400
#define FRAMERATE 60
#define FONT_SIZE 32

int x = 0;
int y = 0;
SDL_Window *win;
SDL_Surface *surface;
SDL_Renderer *renderer;
SDL_Surface *img;
SDL_Surface *bmp;
TTF_Font *font;

void draw() {
    x++;
    if (x > WIDTH) {
        x = 0;
    }
    SDL_Rect rect = {0, 0, WIDTH, HEIGHT};
    SDL_FillRect(surface, &rect, 0xffffffff); // ARGB
    SDL_Rect rect2 = {x, y, WIDTH / 2, HEIGHT / 2};
    SDL_FillRect(surface, &rect2, 0xffff0000); // ARGB

    // 修改像素
    for (int i = 0; i < 100; ++i) {
        ((uint32_t *) (surface->pixels))[WIDTH * 50 + 50 + i] = 0xff0000ff;
    }

    // 图片
    SDL_Rect srcImg = {100, 100, surface->w, surface->h};
    SDL_Rect dstSurface = {0, 0, surface->w, surface->h};
    SDL_BlitSurface(img, &srcImg, surface, &dstSurface);
    SDL_Rect srcBmp = {150, 150, surface->w / 2, surface->h / 2};
    SDL_BlitSurface(bmp, &srcBmp, surface, &dstSurface);

    // 文字
    SDL_Color color = {0, 0, 0, 255};
    SDL_Surface *fontSurface = TTF_RenderUTF8_Blended(font, "Who am I ?", color);
    SDL_Rect srcFont = {0, 0, fontSurface->w, fontSurface->w};
    SDL_BlitSurface(fontSurface, &srcFont, surface, &dstSurface);
    SDL_UpdateWindowSurface(win);
}

void draw2() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_Rect r = {0, 0, 100, 100};
    SDL_RenderFillRect(renderer, &r);
    SDL_RenderPresent(renderer);
}

void eventLoop() {
    while (true) {
        uint32_t begin = SDL_GetTicks();
        draw2();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return;
                }
            }
            printf("Event type: %d\n", event.type);
        }
        uint32_t end = SDL_GetTicks();
        uint32_t cost = end - begin;
        uint32_t frame = 1000 / FRAMERATE;
        int64_t delay = frame - cost;
        if (delay > 0) {
            // 固定帧
            SDL_Delay(frame - cost);
        }
    }
}

bool init() {
    if (TTF_Init() < 0) {
        SDL_Log("Can't init ttf, %s", TTF_GetError());
        return false;
    }
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Can't init window, %s", SDL_GetError());
        return false;
    }
    win = SDL_CreateWindow(
            "Hello World",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WIDTH,
            HEIGHT,
            SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        SDL_Log("can't create window, %s", SDL_GetError());
        return false;
    }

    img = IMG_Load("img\\01.jpeg");
    bmp = SDL_LoadBMP("img\\02.bmp");
    font = TTF_OpenFont("font\\arial.ttf", FONT_SIZE);
    if (font == nullptr) {
        SDL_Log("Can't open font, %s", TTF_GetError());
        return false;
    }
    surface = SDL_GetWindowSurface(win);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Can\t create renderer. %s", SDL_GetError());
        return false;
    }
    return true;
}

void clear() {
    SDL_FreeSurface(img);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
}

int main() {
    if (!init()) {
        return 1;
    }


    eventLoop();
    clear();
    return 0;
}
