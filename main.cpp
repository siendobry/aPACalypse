#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <filesystem>
#include <Windows.h>
#include "include/defs.hpp"
#include "include/app.hpp"
#include "include/gameloop.hpp"


int main(int argc, char* argv[]) {
    std::filesystem::current_path("../");

    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    App app = App();
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }

    if (!app.init()) {
        std::cout << "Failed to initialize an application!" << std::endl;
    } else {
        if (!app.loadTextures()) {
            std::cout << "Failed to load textures!" << std::endl;
        } else {
            GameLoop loop = GameLoop();
            loop.init();
            loop.setEnemySpeedMultiplier(ENEMY_SPEED_MULTIPLIER);
            loop.setBulletSpeedMultiplier(BULLET_SPEED_MULTIPLIER);

            SDL_Event e;
            bool continueExecution = loop.next(&e);
            while (continueExecution) {
                continueExecution = loop.next(&e);

                app.render(loop.getEntities());
            }
        }
    }

    app.close();

    FreeConsole();

    return 0;
}
