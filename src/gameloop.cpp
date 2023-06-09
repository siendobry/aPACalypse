#include <iostream>
#include <random>
#include <SDL_image.h>
#include "../include/gameloop.hpp"
#include "../include/defs.hpp"


void GameLoop::init() {
    gamePaused = false;
    std::random_device rd;
    std::mt19937 tmpGen(rd());
    gen = tmpGen;
    Vector2f playerInitialPosition((WINDOW_WIDTH - PLAYER_WIDTH) / 2.0f, (WINDOW_HEIGHT - PLAYER_HEIGHT) / 2.0f);
    player = Player(playerInitialPosition, Vector2f(0.0f, 0.0f), PLAYER_AMMO);
    enemyHp = ENEMY_HP;
    enemySpeedMultiplier = ENEMY_SPEED_MULTIPLIER;
    bulletSpeedMultiplier = BULLET_SPEED_MULTIPLIER;
}

void GameLoop::spawnEnemy() {
    std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);
    Vector2f randomVector(distribution(gen), distribution(gen));
    Vector2f randomVectorScaled = multiply(randomVector.getNormalized(), WINDOW_DIAGONAL);
    enemies.emplace_back(add(player.getPosition(), std::move(randomVectorScaled)), Vector2f(0.0f, 0.0f), enemyHp, enemySpeedMultiplier);
}

bool GameLoop::next(SDL_Event* e) {
    if (gamePaused) {
        if (SDL_PollEvent(e) != 0 && e->type == SDL_KEYDOWN && !e->key.repeat && e->key.keysym.sym == SDLK_ESCAPE) {
            gamePaused = !gamePaused;
        } else {
            return true;
        }
    }
    while (SDL_PollEvent(e) != 0) {
        if (e->type == SDL_QUIT) {
            return false;
        } else if (e->type == SDL_KEYDOWN && !e->key.repeat) {
            switch (e->key.keysym.sym) {
                case SDLK_w:
                    player.addMovementVector(Vector2f(0.0f, -1.0f));
                    break;
                case SDLK_s:
                    player.addMovementVector(Vector2f(0.0f, 1.0f));
                    break;
                case SDLK_a:
                    player.addMovementVector(Vector2f(-1.0f, 0.0f));
                    break;
                case SDLK_d:
                    player.addMovementVector(Vector2f(1.0f, 0.0f));
                    break;
                case SDLK_ESCAPE:
                    gamePaused = !gamePaused;
                    break;
            }
        } else if (e->type == SDL_KEYUP && !e->key.repeat) {
            switch (e->key.keysym.sym) {
                case SDLK_w:
                    player.addMovementVector(Vector2f(0.0f, 1.0f));
                    break;
                case SDLK_s:
                    player.addMovementVector(Vector2f(0.0f, -1.0f));
                    break;
                case SDLK_a:
                    player.addMovementVector(Vector2f(1.0f, 0.0f));
                    break;
                case SDLK_d:
                    player.addMovementVector(Vector2f(-1.0f, 0.0f));
                    break;
            }
        } else if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT && player.getAmmo() > 0) {
            player.decrementAmmo();
            Vector2f initialPosition = add(player.getPosition(), GUN_POSITION_FIX);
            Vector2f bulletMovementVector = subtract(Vector2f(e->button.x, e->button.y), player.getPosition());
            bullets.emplace_back(initialPosition, bulletMovementVector.getNormalized(), BULLET_SPEED_MULTIPLIER);
        }
    }

    player.move();
    for (Enemy& enemy : enemies) {
        Vector2f enemyToPlayerVector = subtract(player.getPosition(), enemy.getPosition());
        enemy.move(enemyToPlayerVector.getNormalized());
    }
    for (Bullet& bullet : bullets) {
        bullet.move();
    }

    for (Enemy& enemy : enemies) {
        if (player.collision(enemy)) {
            return false;
        }
    }

    bool enemyShot;
    for (int i = 0; i < bullets.size(); ++i) {
        enemyShot = false;
        for (int j = 0; j < enemies.size(); ++j) {
            if (bullets.at(i).collision(enemies.at(j))) {
                score += 10;
                enemyShot = true;
                enemies.erase(std::remove(enemies.begin(), enemies.end(), enemies.at(j)), enemies.end());
                break;
            }
        }
        if (enemyShot) {
            player.incrementAmmo();
            bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets.at(i)), bullets.end());
        }
    }

    std::uniform_int_distribution<int> distribution(0, 199);
    if (distribution(gen) == 0) {
        spawnEnemy();
    }

    return true;
}

std::vector<Entity> GameLoop::getEntities() {
    std::vector<Entity> entities;
    entities.reserve(1 + enemies.size() + bullets.size());
    entities.insert(entities.end(), player);
    entities.insert(entities.end(), enemies.begin(), enemies.end());
    entities.insert(entities.end(), bullets.begin(), bullets.end());
    return entities;
}