#ifndef APACALYPSE_BULLET_HPP
#define APACALYPSE_BULLET_HPP

#include "../include/entity.hpp"

class Bullet : public Entity {
public:
    Bullet(Vector2f position, Vector2f movementVector, float speedMultiplier = 1.0f);
    void move() override;
private:
    float speedMultiplier;
};

#endif //APACALYPSE_BULLET_HPP
