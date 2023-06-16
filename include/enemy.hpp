#ifndef APACALYPSE_ENEMY_HPP
#define APACALYPSE_ENEMY_HPP

#include "../include/entity.hpp"

class Enemy : public Entity {
public:
    Enemy(Vector2f position, Vector2f movementVector = Vector2f(0.0f, 0.0f), int hp = 1, float speedMultiplier = 1.0f);
    void move(Vector2f vec) override;
    void setFacingDirection(Vector2f moveDirection);
private:
    int hp;
};

#endif //APACALYPSE_ENEMY_HPP
