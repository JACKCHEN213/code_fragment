#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "core/Resource.h"
#include "core/Ball.h"

#undef main
#define WIDTH 400
#define HEIGHT 400
#define FRAMERATE 60
#define FONT_SIZE 32
#define BALL_COUNT 5

int x = 0;
int y = 0;
SDL_Window *win;
SDL_Surface *surface;
SDL_Renderer *renderer;
SDL_Surface *img;
SDL_Surface *bmp;
SDL_Texture *bmpTexture;
TTF_Font *font;
SDL_Surface *ball;
SDL_Texture *ballTexture;
Ball *ballObjs[BALL_COUNT];

void createBallObjs() {
    for (int i = 0; i < BALL_COUNT; ++i) {
        ballObjs[i] = Ball_Create(70 * i, 10, rand() % 10 - 5);
    }
}

void destroyBallObjs() {
    for (auto & ballObj : ballObjs) {
        Ball_Destroy(ballObj);
    }
}

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
    // 线条
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 0, 0, 100, 100);
    // 批量绘制线条
    SDL_Point points[] = {{50, 50}, {100, 200}, {300, 150}};
    SDL_RenderDrawLines(renderer, points, sizeof(points) / sizeof(SDL_Point));
    // 渲染图片
    int w;
    int h;
    SDL_QueryTexture(bmpTexture, nullptr, nullptr, &w, &h);
    SDL_Rect sr = {0, 0, w, h};
    SDL_Rect dr = {0, 100, 150, 150};
    SDL_RenderCopy(renderer, bmpTexture, &sr, &dr);
    // 旋转、翻转
    static double angle = 0;
    SDL_Rect dr2 = {200, 100, 150, 150};
    angle++;
    SDL_RenderCopyEx(renderer, bmpTexture, &sr, &dr2, angle, nullptr,
                     static_cast<const SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL));
    // 缩放
    static float scaleY = 1;
    scaleY += 0.01;
    if (scaleY > 2) {
        scaleY = 0.1;
    }
    SDL_RenderSetScale(renderer, 1, scaleY);
    // 偏移
    SDL_Rect viewPort = {100, 100, 200, 200};
    SDL_RenderSetViewport(renderer, &viewPort);
    SDL_RenderPresent(renderer);
}

void draw3()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    static double angle = 0;
    angle++;
    for (int i = 0; i < 5; ++i) {
        SDL_Rect destRect = {i * 70, 0, 60, 60};
        SDL_RenderCopyEx(renderer, ballTexture, nullptr, &destRect, angle + i, nullptr, SDL_FLIP_NONE);
    }
    SDL_RenderPresent(renderer);
}

void draw4 () {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    for (auto & ballObj : ballObjs) {
        Ball_Draw(ballObj, renderer);
    }
    SDL_RenderPresent(renderer);
}

void eventLoop() {
    while (true) {
        uint32_t begin = SDL_GetTicks();
        draw4();
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
        uint32_t delay = frame - cost;
        // FIX: 修复卡顿问题。运行时间大于帧数，导致休息时间过长
        if (delay > 0 && delay <= frame) {
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

    surface = SDL_GetWindowSurface(win);
    if (surface == nullptr) {
        SDL_Log("Can't get window surface, %s", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Can't create renderer, %s", SDL_GetError());
        return false;
    }

    img = IMG_Load("img\\01.jpeg");
    if (img == nullptr) {
        SDL_Log("Can't load img, %s", SDL_GetError());
        return false;
    }
    bmp = SDL_LoadBMP("img\\02.bmp");
    if (bmp == nullptr) {
        SDL_Log("Can't load img, %s", SDL_GetError());
        return false;
    }
    bmpTexture = SDL_CreateTextureFromSurface(renderer, bmp);
    if (bmpTexture == nullptr) {
        SDL_Log("Can't get texture, %s", SDL_GetError());
        return false;
    }
    font = TTF_OpenFont("font\\arial.ttf", FONT_SIZE);
    if (font == nullptr) {
        SDL_Log("Can't open font, %s", TTF_GetError());
        return false;
    }
    ball = IMG_Load("img\\small_ball.png");
    if (ball == nullptr) {
        SDL_Log("Can't load img, %s", SDL_GetError());
        return false;
    }
    ballTexture = SDL_CreateTextureFromSurface(renderer, ball);
    if (ballTexture == nullptr) {
        SDL_Log("Can't get texture, %s", SDL_GetError());
        return false;
    }
    if (Resource_Load(renderer, "img\\small_ball.png")) {
        return false;
    }
    createBallObjs();
    return true;
}

void clear() {
    destroyBallObjs();
    Resource_Unload();
    SDL_DestroyTexture(ballTexture);
    SDL_FreeSurface(ball);
    SDL_DestroyTexture(bmpTexture);
    SDL_FreeSurface(bmp);
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
