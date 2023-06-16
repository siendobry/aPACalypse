#ifndef APACALYPSE_GAMELOOP_HPP
#define APACALYPSE_GAMELOOP_HPP

#include <vector>
#include <random>
#include "player.hpp"
#include "enemy.hpp"
#include "bullet.hpp"

class GameLoop {
public:
    explicit GameLoop() = default;
    void init();
    void spawnEnemy();
    bool next(SDL_Event* e);
    std::vector<Entity*> getEntities();
    void setAmmo(int ammo) {player.setAmmo(ammo);}
    [[nodiscard]] int getAmmo() const {return player.getAmmo();}
    void setHp(int hp) {enemyHp = hp;}
    void setBulletSpeedMultiplier(float multiplier) { bulletSpeedMultiplier = multiplier;}
    void setEnemySpeedMultiplier(float multiplier) {enemySpeedMultiplier = multiplier;}
    [[nodiscard]] unsigned long long getScore() const {return score;}
private:
    bool gamePaused;
    std::mt19937 gen;
    unsigned long long score;
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    int enemyHp;
    float enemySpeedMultiplier;
    float bulletSpeedMultiplier;
};

#endif //APACALYPSE_GAMELOOP_HPP
