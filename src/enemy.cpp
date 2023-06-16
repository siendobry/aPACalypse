#include "../include/defs.hpp"
#include "../include/enemy.hpp"

Enemy::Enemy(Vector2f position, Vector2f movementVector, int hp, float speedMultiplier)
: Entity(position, movementVector, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_TEXTURE, speedMultiplier), hp(hp) {
}

void Enemy::move(Vector2f vec) {
    position = add(std::move(position), multiply(vec, speedMultiplier));
}

void Enemy::setFacingDirection(Vector2f moveDirection) {
    if (moveDirection.x >= 0) {
        Entity::setFacingDirection(SDL_FLIP_NONE);
    } else {
        Entity::setFacingDirection(SDL_FLIP_HORIZONTAL);
    }
}
