#include "../include/defs.hpp"
#include "../include/player.hpp"

Player::Player(Vector2f position, Vector2f movementVector, int ammo, float speedMultiplier)
: Entity(position, movementVector, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_TEXTURE, speedMultiplier), ammo(ammo) {
}

void Player::move() {
    float movementVectorX = movementVector.x;
    float movementVectorY = movementVector.y;
    if ((position.x <= 0 && movementVectorX < 0)
     || (position.x >= WINDOW_WIDTH - PLAYER_WIDTH && movementVectorX > 0)) {
        movementVector.x = 0.0f;
    }
    if ((position.y <= 0 && movementVectorY < 0)
     || (position.y >= WINDOW_HEIGHT - PLAYER_HEIGHT && movementVectorY > 0)) {
        movementVector.y = 0.0f;
    }
    Entity::move();
    movementVector.x = movementVectorX;
    movementVector.y = movementVectorY;
}