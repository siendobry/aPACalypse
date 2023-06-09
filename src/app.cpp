#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "../include/defs.hpp"
#include "../include/app.hpp"


App::App() : window(nullptr), renderer(nullptr) {
}

bool App::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init ERROR: " << SDL_GetError() << std::endl;
        return false;
    } else {
        window = SDL_CreateWindow(
                "aPACalypse",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                WINDOW_WIDTH, WINDOW_HEIGHT,
                SDL_WINDOW_SHOWN
        );
        if (window == nullptr) {
            std::cout << "SDL_CreateWindow ERROR: " << SDL_GetError() << std::endl;
            return false;
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == nullptr) {
                std::cout << "SDL_CreateRenderer ERROR: " << SDL_GetError() << std::endl;
                return false;
            }
        }
    }
    return true;
}

bool App::loadTextures() {
    textures[PLAYER_TEXTURE] = IMG_LoadTexture(renderer, PLAYER_IDLE_TEXTURE_PATH.c_str());
    if (textures[PLAYER_TEXTURE] == nullptr) {
        std::cout << "IMG_Load ERROR: " << IMG_GetError() << std::endl;
        return false;
    }
    textures[ENEMY_TEXTURE] = IMG_LoadTexture(renderer, ENEMY_TEXTURE_PATH.c_str());
    if (textures[ENEMY_TEXTURE] == nullptr) {
        std::cout << "IMG_Load ERROR: " << IMG_GetError() << std::endl;
        return false;
    }
    textures[BULLET_TEXTURE] = IMG_LoadTexture(renderer, BULLET_TEXTURE_PATH.c_str());
    if (textures[BULLET_TEXTURE] == nullptr) {
        std::cout << "IMG_Load ERROR: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;
}

void App::render(std::vector<Entity> entities) {
    SDL_Rect entityQuad;
    SDL_Rect renderQuad;
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(renderer);
    for (Entity& entity : entities) {
        entityQuad.x = 0;
        entityQuad.y = 0;
        entityQuad.w = entity.getWidth();
        entityQuad.h = entity.getHeight();

        renderQuad.x = entity.getPosition().x;
        renderQuad.y = entity.getPosition().y;
        renderQuad.w = entity.getWidth();
        renderQuad.h = entity.getHeight();

        SDL_RenderCopy(renderer, textures[entity.getTextureId()], &entityQuad, &renderQuad);
    }
    SDL_RenderPresent(renderer);
}

void App::close() {
    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    for (SDL_Texture* texture : textures) {
        SDL_DestroyTexture(texture);
    }

    SDL_Quit();
    IMG_Quit();
}
