#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "core/Resource.h"
#include "core/Ball.h"
#include "core/RectShape.h"
#include "utils/color.h"
#include "core/Cursor.h"
#include "core/Slider.h"
#include "core/RectInRect.h"
#include "core/Eye.h"
#include "core/Text.h"

#undef main
#define WIDTH 400
#define HEIGHT 400
#define FRAMERATE 60
#define FONT_SIZE 32
#define BALL_COUNT 5
#define RECT_SHAPE_COUNT 3

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
// RectShape *rectShapes[RECT_SHAPE_COUNT];
RectShape *firstRectShape;
RectShape *lastRectShape;
DisplayObject *cursor;
DisplayObject *slider;
DisplayObject *rectInRect;
DisplayObject *eye1;
DisplayObject *text1;
int textCount = 0;

void addRectShape(RectShape *rectShape) {
    if (lastRectShape != nullptr) {
        lastRectShape->next = rectShape;
        rectShape->prev = lastRectShape;
        lastRectShape = rectShape;
    } else {
        lastRectShape = rectShape;
        firstRectShape = rectShape;
    }
}

void createRectShapeObjs() {
    firstRectShape = lastRectShape = nullptr;
    for (int i = 0; i < RECT_SHAPE_COUNT; ++i) {
        addRectShape(RectShape_Create((float) (i * 100), 0, 80, 80, getARGB()));
        // rectShapes[i] = RectShape_Create((float)(i * 100), 0, 80, 80, getARGB());
    }
}

void createBallObjs() {
    for (int i = 0; i < BALL_COUNT; ++i) {
        ballObjs[i] = Ball_Create(
                (float) (70 * i), 10,
                dis(gen) % 10 - 5,
                (float) (dis(gen) % 4 + 1),
                (float) (dis(gen) % 4 + 1));
    }
}

void destroyBallObjs() {
    for (auto &ballObj: ballObjs) {
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
    SDL_Point points[] = {{50,  50},
                          {100, 200},
                          {300, 150}};
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

void draw3() {
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

void draw4() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    // for (auto &rectShape: rectShapes) {
    //     RectShape_Draw(rectShape, renderer);
    // }
    RectShape *item = firstRectShape;
    while (item != nullptr) {
        RectShape_Draw(item, renderer);
        item = item->next;
    }
    for (auto &ballObj: ballObjs) {
        Ball_Draw(ballObj, renderer);
    }
    DisplayObject_Draw(cursor, renderer);
    DisplayObject_Draw(slider, renderer);
    DisplayObject_Draw(rectInRect, renderer);
    DisplayObject_Draw(eye1, renderer);
    DisplayObject_Draw(text1, renderer);
    SDL_RenderPresent(renderer);
}

void eventLoop() {
    while (true) {
        uint32_t begin = SDL_GetTicks();
        draw4();
        SDL_Event event;
        RectShape *item = lastRectShape;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    return;
                case SDL_MOUSEMOTION:
                    DisplayObject_OnMouseMove(cursor, &event);
                    DisplayObject_OnMouseMove(slider, &event);
                    DisplayObject_OnMouseMove(rectInRect, &event);
                    DisplayObject_OnMouseMove(eye1, &event);
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    while (item != nullptr) {
                        if (RectShape_OnMouseEvent(item, &event) == SDL_TRUE) {
                            if (item != lastRectShape) {
                                if (item->prev != nullptr) {
                                    item->prev->next = item->next;
                                } else {
                                    firstRectShape = item->next;
                                }
                                item->next->prev = item->prev;
                                item->next = nullptr;
                                addRectShape(item);
                            }
                            break;
                        }
                        item = item->prev;
                    }
                    // for (int i = RECT_SHAPE_COUNT - 1; i >= 0; --i) {
                    //     if (RectShape_OnMouseEvent(rectShapes[i], &event) == SDL_TRUE) {
                    //         break;
                    //     }
                    // }
                    break;
                case SDL_KEYDOWN:
                    SDL_Log("Key down: %d", event.key.keysym.sym);
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        return;
                    } else if (event.key.keysym.sym == SDLK_SPACE) {
                        textCount++;
                        char buf[16];
                        sprintf(buf, "Count: %d", textCount);
                        Text_Set(text1, buf);
                    }
                    break;
                case SDL_KEYUP:
                    SDL_Log("Key up: %d", event.key.keysym.sym);
                    break;
            }
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
    createRectShapeObjs();
    SDL_SetCursor(Resource_GetCursor());
    cursor = Cursor_Create(0, 0, 50, 50);
    slider = Slider_Create(50, 100, 200, 10, 30, 20);
    rectInRect = RectInRect_Create(50, 150, 200, 100, 30, 20);
    eye1 = Eye_Create(300, 100, 30, 10);
    text1 = Text_Create("font/arial.ttf", "I have a dream", 18, 0xff00ff00, 100 ,300);
    return true;
}

void clear() {
    // for (auto &rectShape: rectShapes) {
    //     RectShape_Destroy(rectShape);
    // }
    Text_Destroy(text1);
    Eye_Destroy(eye1);
    RectInRect_Destroy(rectInRect);
    Slider_Destroy(slider);
    Cursor_Destroy(cursor);
    RectShape *item = firstRectShape;
    while (item != nullptr) {
        RectShape *current = item;
        item = item->next;
        RectShape_Destroy(current);
    }
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

    // SDL_ShowCursor(0);
    eventLoop();
    clear();
    return 0;
}
