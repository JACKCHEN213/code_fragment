#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <windows.h>

const int GAME_WINDOWS_WIDTH = 934;
const int GAME_WINDOWS_HEIGHT = 462;

SDL_Window *gWindows = nullptr;   // 窗口
SDL_Surface *gSurface = nullptr;  // 窗口的外表
SDL_Surface *bgSurface = nullptr; // 背景图片
SDL_Renderer *gRenderer = nullptr;

bool init() {
    // 对SDL库进行初始化
    // 初始化视频和音频
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("初始化失败, %s\n", SDL_GetError());
        return false;
    }
    // 创建游戏窗口
    gWindows = SDL_CreateWindow("我的魂斗罗",            // 标题
                                SDL_WINDOWPOS_UNDEFINED, // 开始x位置
                                SDL_WINDOWPOS_UNDEFINED, // 开始
                                GAME_WINDOWS_WIDTH,      // 高度
                                GAME_WINDOWS_HEIGHT,     // 宽度
                                SDL_WINDOW_SHOWN); // 宽口是显示的，而不是隐藏的
    if (gWindows == nullptr) {
        printf("创建游戏窗口失败, %s\n", SDL_GetError());
        return false;
    }
    // 创建Surface
    gSurface = SDL_GetWindowSurface(gWindows);
    if (gSurface == nullptr) {
        printf("创建窗口的外表失败, %s\n", SDL_GetError());
    }
    gRenderer = SDL_CreateRenderer(
            gWindows,
            -1, // 序号，第一个渲染器
            SDL_RENDERER_ACCELERATED |
            SDL_RENDERER_PRESENTVSYNC); // 硬件加速 | 刷新频率同步
    if (gRenderer == nullptr) {
        printf("创建渲染器失败, %s\n", SDL_GetError());
    }
    return true;
}

bool loadResource() {
    bgSurface = SDL_LoadBMP("res/hundouluo.bmp");
    if (bgSurface == nullptr) {
        printf("加载图片%s失败, %s\n", "huodouluo.bmp", SDL_GetError());
        return false;
    }
    return true;
}

/**
 * 加载图片
 * @param file 文件路径
 * @return 被加载的图片纹理
 */
SDL_Texture *loadImage(const char *file) {
    SDL_Texture *texture = IMG_LoadTexture(gRenderer, file);
    return texture;
}

/**
 * 显示图片
 * @param file 要渲染的图片
 */
bool showImage(int x, int y, const char *file) {
    SDL_Texture *texture = loadImage(file);
    if (texture == nullptr) {
        printf("加载图片纹理失败, %s\n", SDL_GetError());
        return false;
    }
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    // 获取图片的高宽
    SDL_QueryTexture(texture, nullptr, nullptr, &pos.w, &pos.h);
    SDL_RenderCopy(
            gRenderer,
            texture,
            nullptr,
            &pos
    );
    return true;
}

void close() {}

int main(int argc, char *args[]) {
    if (!init()) {
        return 1;
    }

    // 加载资源
    if (!loadResource()) {
        return 1;
    }

    // 显示背景图片
    SDL_BlitSurface(bgSurface, nullptr, gSurface, nullptr);

    // 更新缓存，刷新窗口
    SDL_UpdateWindowSurface(gWindows);

    // 事件循环
    bool is_stop = false;
    // 定义一个SDL事件
    SDL_Event event;
    while (!is_stop) {
        if (!showImage(0, 0, "res/hundouluo.png")) {
            is_stop = true;
        }
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    is_stop = true;
                    break;
                } else if (event.key.keysym.sym == SDLK_UP) {
                    if (!showImage(100, 100, "res/map/map1.png")) {
                        is_stop = true;
                        break;
                    }
                } else if (event.key.keysym.sym == SDLK_DOWN) {
                    //
                }
                SDL_RenderPresent(gRenderer);
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                //
            }
        }
        Sleep(10);
    }

    close();
    return 0;
}
