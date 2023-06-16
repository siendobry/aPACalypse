#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../include/defs.hpp"
#include "../include/app.hpp"
#include "../include/text.hpp"


App::App() : window(nullptr), renderer(nullptr), scoreText("") {
}

bool App::init() {
    int imgFlags = IMG_INIT_PNG;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init ERROR: " << SDL_GetError() << std::endl;
        return false;
    } else if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "IMG_Init ERROR: " << IMG_GetError() << std::endl;
        return false;
    } else if (TTF_Init() == -1) {
        std::cout << "TTF_Init ERROR: " << TTF_GetError() << std::endl;
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

bool App::loadResources() {
    font = TTF_OpenFont(FONT_PATH.c_str(), 28);
    if (font == nullptr) {
        std::cout << "TTF_OpenFont ERROR: " << TTF_GetError() << std::endl;
        return false;
    }

    titleTexture = IMG_LoadTexture(renderer, TITLE_TEXTURE_PATH.c_str());
    if (titleTexture == nullptr) {
        std::cout << "IMG_Load ERROR: " << IMG_GetError() << std::endl;
        return false;
    }

    auto textColor = SDL_Color(0, 0, 0);
    Text startText = Text("PRESS ENTER TO START");
    if (!startText.init(renderer, font, textColor)) {
        std::cout << "Text initialization failed" << std::endl;
        return false;
    }
    startText.setPosition((WINDOW_WIDTH - startText.getWidth()) / 2, 320);
    mainMenuTexts.push_back(startText);
    Text instructionText = Text("INSTRUCTIONS: MOVEMENT - WASD, SHOOTING - LEFT MOUSE BUTTON");
    if (!instructionText.init(renderer, font, textColor)) {
        std::cout << "Text initialization failed" << std::endl;
        return false;
    }
    instructionText.setPosition((WINDOW_WIDTH - instructionText.getWidth()) / 2, 656);
    mainMenuTexts.push_back(instructionText);
    Text escapeText = Text("PRESS Q TO QUIT");
    if (!escapeText.init(renderer, font, textColor)) {
        std::cout << "Text initialization failed" << std::endl;
        return false;
    }
    escapeText.setPosition((WINDOW_WIDTH - escapeText.getWidth()) / 2, 384);
    mainMenuTexts.push_back(escapeText);
    endScreenTexts.push_back(escapeText);
    Text againText = Text("PRESS ENTER TO ENTER MAIN MENU");
    if (!againText.init(renderer, font, textColor)) {
        std::cout << "Text initialization failed" << std::endl;
        return false;
    }
    againText.setPosition((WINDOW_WIDTH - againText.getWidth()) / 2, 320);
    endScreenTexts.push_back(againText);


    entityTextures[PLAYER_TEXTURE] = IMG_LoadTexture(renderer, PLAYER_IDLE_TEXTURE_PATH.c_str());
    if (entityTextures[PLAYER_TEXTURE] == nullptr) {
        std::cout << "IMG_Load ERROR: " << IMG_GetError() << std::endl;
        return false;
    }
    entityTextures[ENEMY_TEXTURE] = IMG_LoadTexture(renderer, ENEMY_TEXTURE_PATH.c_str());
    if (entityTextures[ENEMY_TEXTURE] == nullptr) {
        std::cout << "IMG_Load ERROR: " << IMG_GetError() << std::endl;
        return false;
    }
    entityTextures[BULLET_TEXTURE] = IMG_LoadTexture(renderer, BULLET_TEXTURE_PATH.c_str());
    if (entityTextures[BULLET_TEXTURE] == nullptr) {
        std::cout << "IMG_Load ERROR: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

bool App::loadScoreResource(unsigned long long score) {
    auto textColor = SDL_Color(0, 0, 0);
    scoreText = Text("SCORE: " + std::to_string(score));
    if (!scoreText.init(renderer, font, textColor)) {
        std::cout << "Text initialization failed" << std::endl;
        return false;
    }
    return true;
}

App::AppState App::handleState(SDL_Event* e) {
    while (SDL_PollEvent(e) != 0) {
        if (e->type == SDL_QUIT) {
            return App::ESCAPE;
        } else if (e->type == SDL_KEYDOWN) {
            switch (e->key.keysym.sym) {
                case SDLK_RETURN:
                    return App::START;
                case SDLK_q:
                    return App::ESCAPE;
                default:
                    return App::NOTHING;
            }
        }
    }
    return App::NOTHING;
}

void App::renderMainMenu() {
    SDL_Rect originalQuad;
    SDL_Rect renderQuad;

    originalQuad.x = 0;
    originalQuad.y = 0;
    originalQuad.w = TITLE_WIDTH;
    originalQuad.h = TITLE_HEIGHT;

    renderQuad.x = (WINDOW_WIDTH - 3 * TITLE_WIDTH) / 2;
    renderQuad.y = 32;
    renderQuad.w = 3 * TITLE_WIDTH;
    renderQuad.h = 3 * TITLE_HEIGHT;

    SDL_RenderCopy(renderer, titleTexture, &originalQuad, &renderQuad);

    for (Text text : mainMenuTexts) {
        originalQuad.x = 0;
        originalQuad.y = 0;
        originalQuad.w = text.getWidth();
        originalQuad.h = text.getHeight();

        renderQuad.x = text.getX();
        renderQuad.y = text.getY();
        renderQuad.w = text.getWidth();
        renderQuad.h = text.getHeight();

        SDL_RenderCopy(renderer, text.getTexture(), &originalQuad, &renderQuad);
    }

    SDL_RenderPresent(renderer);
}

void App::renderGameInfo(int ammo, unsigned long long score) {
    auto textColor = SDL_Color(0, 0, 0);
    Text ammoText = Text("AMMO: " + std::to_string(ammo));
    if (!ammoText.init(renderer, font, textColor)) {
        std::cout << "Text initialization failed" << std::endl;
    }

    Text scoreTextInGame = Text("SCORE: " + std::to_string(score));
    if (!scoreTextInGame.init(renderer, font, textColor)) {
        std::cout << "Text initialization failed" << std::endl;
    }

    SDL_Rect originalQuad;
    SDL_Rect renderQuad;

    originalQuad.x = 0;
    originalQuad.y = 0;
    originalQuad.w = ammoText.getWidth();
    originalQuad.h = ammoText.getHeight();

    renderQuad.x = 16;
    renderQuad.y = WINDOW_HEIGHT - ammoText.getHeight() - 16;
    renderQuad.w = ammoText.getWidth();
    renderQuad.h = ammoText.getHeight();

    SDL_RenderCopy(renderer, ammoText.getTexture(), &originalQuad, &renderQuad);

    originalQuad.x = 0;
    originalQuad.y = 0;
    originalQuad.w = scoreTextInGame.getWidth();
    originalQuad.h = scoreTextInGame.getHeight();

    renderQuad.x = 16;
    renderQuad.y = 16;
    renderQuad.w = ammoText.getWidth();
    renderQuad.h = ammoText.getHeight();

    SDL_RenderCopy(renderer, scoreTextInGame.getTexture(), &originalQuad, &renderQuad);
}

void App::renderEndScreen(unsigned long long score) {
    if (!loadScoreResource(score)) {
        std::cout << "Score cannot be rendered" << std::endl;
    }

    SDL_Rect originalQuad;
    SDL_Rect renderQuad;

    originalQuad.x = 0;
    originalQuad.y = 0;
    originalQuad.w = scoreText.getWidth();
    originalQuad.h = scoreText.getHeight();

    renderQuad.x = (WINDOW_WIDTH - 3 * scoreText.getWidth()) / 2;
    renderQuad.y = 32;
    renderQuad.w = 3 * scoreText.getWidth();
    renderQuad.h = 3 * scoreText.getHeight();

    SDL_RenderCopy(renderer, scoreText.getTexture(), &originalQuad, &renderQuad);

    for (Text text : endScreenTexts) {
        originalQuad.x = 0;
        originalQuad.y = 0;
        originalQuad.w = text.getWidth();
        originalQuad.h = text.getHeight();

        renderQuad.x = text.getX();
        renderQuad.y = text.getY();
        renderQuad.w = text.getWidth();
        renderQuad.h = text.getHeight();

        SDL_RenderCopy(renderer, text.getTexture(), &originalQuad, &renderQuad);
    }

    SDL_RenderPresent(renderer);
}

void App::renderEntities(const std::vector<Entity*>& entities) {
    SDL_Rect entityQuad;
    SDL_Rect renderQuad;
    for (Entity* entity : entities) {
        entityQuad.x = 0;
        entityQuad.y = 0;
        entityQuad.w = entity->getWidth();
        entityQuad.h = entity->getHeight();

        renderQuad.x = entity->getPosition().x;
        renderQuad.y = entity->getPosition().y;
        renderQuad.w = entity->getWidth();
        renderQuad.h = entity->getHeight();

        SDL_RenderCopyEx(
                renderer,
                entityTextures[entity->getTextureId()],
                &entityQuad,
                &renderQuad,
                0,
                nullptr,
                entity->getFacingDirection()
        );
    }
    SDL_RenderPresent(renderer);
}

void App::clear() {
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(renderer);
}

void App::close() {
    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyTexture(titleTexture);
    titleTexture = nullptr;
    for (SDL_Texture* texture : entityTextures) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    TTF_CloseFont(font);
    font = nullptr;

    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}
