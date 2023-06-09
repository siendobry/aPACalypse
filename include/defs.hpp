#ifndef APACALYPSE_DEFS_HPP
#define APACALYPSE_DEFS_HPP

#include <string>
#include <cmath>
#include "vector.hpp"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const float WINDOW_DIAGONAL = sqrt(pow(WINDOW_WIDTH, 2) + pow(WINDOW_WIDTH, 2));
const int FPS_WITH_VSYNC = 60;

enum {
    PLAYER_TEXTURE,
    ENEMY_TEXTURE,
    BULLET_TEXTURE,
    ALL_TEXTURES_NUMBER
};

const int PLAYER_WIDTH = 26;
const int PLAYER_HEIGHT = 26;

const int ENEMY_WIDTH = 32;
const int ENEMY_HEIGHT = 32;

const int BULLET_WIDTH = 8;
const int BULLET_HEIGHT = 4;

#define GUN_POSITION_FIX Vector2f(PLAYER_WIDTH - 4.0f, (PLAYER_HEIGHT - 2.0f) / 2.0f)

const int PLAYER_AMMO = 1000;
const int ENEMY_HP = 1;
const float ENEMY_SPEED_MULTIPLIER = 0.5f;
const float BULLET_SPEED_MULTIPLIER = 4.0f;

const std::string PLAYER_IDLE_TEXTURE_PATH = "resources/gfx/idle.png";
const std::string PLAYER_MOVE_TEXTURE_PATH = "resources/gfx/move.png";
const std::string ENEMY_TEXTURE_PATH = "resources/gfx/enemy.png";
const std::string BULLET_TEXTURE_PATH = "resources/gfx/bullet.png";

const int PLAYER_IDLE_ANIMATION_FRAMES = 2;
const int PLAYER_MOVE_ANIMATION_FRAMES = 4;
const int ENEMY_ANIMATION_FRAMES = 8;

#endif //APACALYPSE_DEFS_HPP
