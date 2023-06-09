#ifndef APACALYPSE_ENTITY_HPP
#define APACALYPSE_ENTITY_HPP

#include <SDL.h>
#include <string>
#include "../include/vector.hpp"

class Entity {
public:
    virtual void move();
    virtual void move(Vector2f vec);
    void addMovementVector(Vector2f vec);
    virtual bool collision(Entity& other) const;
    Vector2f getPosition() {return position;}
    float getWidth() {return width;}
    float getHeight() {return height;}
    int getTextureId() {return textureId;}
    bool operator==(const Entity& other);
protected:
    Entity() = default;
    Entity(Vector2f position, Vector2f movementVector, float width, float height, int textureId);
protected:
    Vector2f position;
    Vector2f movementVector;
    float width;
    float height;
    int textureId;
};

#endif //APACALYPSE_ENTITY_HPP
