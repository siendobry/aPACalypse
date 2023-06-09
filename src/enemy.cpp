#include "../include/defs.hpp"
#include "../include/enemy.hpp"

Enemy::Enemy(Vector2f position, Vector2f movementVector, int hp, float speedMultiplier)
: Entity(position, movementVector, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_TEXTURE), hp(hp), speedMultiplier(speedMultiplier) {
}

void Enemy::move(Vector2f vec) {
    position = add(std::move(position), multiply(vec, speedMultiplier));
}
