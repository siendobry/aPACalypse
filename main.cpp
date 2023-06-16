#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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

    if (!app.init()) {
        std::cout << "Failed to initialize an application!" << std::endl;
    } else {
        if (!app.loadResources()) {
            std::cout << "Failed to load entityTextures!" << std::endl;
        } else {
            SDL_Event e;
            while (true) {
                App::AppState mainMenuOutput = App::NOTHING;
                app.clear();
                app.renderMainMenu();
                while (mainMenuOutput == App::NOTHING) {
                    mainMenuOutput = app.handleState(&e);
                }
                if (mainMenuOutput == App::ESCAPE) {
                    return 0;
                }

                GameLoop loop = GameLoop();
                loop.init();
                loop.setEnemySpeedMultiplier(ENEMY_SPEED_MULTIPLIER);
                loop.setBulletSpeedMultiplier(BULLET_SPEED_MULTIPLIER);

                bool continueExecution = loop.next(&e);
                while (continueExecution) {
                    continueExecution = loop.next(&e);
                    app.clear();
                    app.renderEntities(loop.getEntities());
                    app.renderGameInfo(loop.getAmmo(), loop.getScore());
                }

                App::AppState endScreenOutput = App::NOTHING;
                app.clear();
                app.renderEndScreen(loop.getScore());
                while (endScreenOutput == App::NOTHING) {
                    endScreenOutput = app.handleState(&e);
                }
                if (endScreenOutput == App::ESCAPE) {
                    return 0;
                }
            }
        }
    }

    app.close();

    FreeConsole();

    return 0;
}
