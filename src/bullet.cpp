#include <iostream>
#include "../include/defs.hpp"
#include "../include/bullet.hpp"
#include "../include/vector.hpp"

Bullet::Bullet(Vector2f position, Vector2f movementVector, float speedMultiplier)
: Entity(position, movementVector, BULLET_WIDTH, BULLET_HEIGHT, BULLET_TEXTURE), speedMultiplier(speedMultiplier) {
}

void Bullet::move() {
    position = add(std::move(position), multiply(movementVector, speedMultiplier));
}
