#ifndef APACALYPSE_APP_HPP
#define APACALYPSE_APP_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include "entity.hpp"
#include "text.hpp"


class App {
public:
    enum AppState {
        NOTHING,
        START,
        ESCAPE
    };
public:
    App();
    bool init();
    bool loadResources();
    bool loadScoreResource(unsigned long long score);
    AppState handleState(SDL_Event* e);
    void renderMainMenu();
    void renderGameInfo(int ammo, unsigned long long score);
    void renderEndScreen(unsigned long long score);
    void renderEntities(const std::vector<Entity*>& entities);
    void clear();
    void close();
    SDL_Window* getWindow() {return window;}
    SDL_Renderer* getRenderer() {return renderer;}
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    TTF_Font* font;

    SDL_Texture* titleTexture;
    std::vector<Text> mainMenuTexts = {};
    std::vector<Text> endScreenTexts = {};
    Text scoreText;

    SDL_Texture* entityTextures[ALL_TEXTURES_NUMBER];
};

#endif //APACALYPSE_APP_HPP
