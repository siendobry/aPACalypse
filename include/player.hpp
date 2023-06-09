#ifndef APACALYPSE_PLAYER_HPP
#define APACALYPSE_PLAYER_HPP

#include "../include/entity.hpp"

class Player : public Entity {
public:
    Player() = default;
    Player(Vector2f position, Vector2f movementVector = Vector2f(0.0f, 0.0f), int ammo = 10);
    void move() override;
    void incrementAmmo() {++ammo;}
    void decrementAmmo() {--ammo;}
    int getAmmo() const {return ammo;}
    void setAmmo(int ammo) {ammo = ammo;}
private:
    int ammo;
};

#endif //APACALYPSE_PLAYER_HPP
