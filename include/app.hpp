#ifndef APACALYPSE_APP_HPP
#define APACALYPSE_APP_HPP

#include <SDL.h>
#include <vector>
#include "entity.hpp"

class App {
public:
    App();
    bool init();
    bool loadTextures();
    void render(std::vector<Entity> entities);
    void close();
    SDL_Window* getWindow() {return window;}
    SDL_Renderer* getRenderer() {return renderer;}
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* textures[ALL_TEXTURES_NUMBER];
};

#endif //APACALYPSE_APP_HPP
