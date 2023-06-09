#include "../include/entity.hpp"

Entity::Entity(Vector2f position, Vector2f movementVector, float width, float height, int textureId)
: position(position), movementVector(movementVector), width(width), height(height), textureId(textureId) {
}

void Entity::move() {
    position = add(position, movementVector);
}

void Entity::move(Vector2f vec) {
    position = add(position, vec);
}

void Entity::addMovementVector(Vector2f vec) {
    movementVector = add(movementVector, vec);
}

bool Entity::collision(Entity &other) const {
    return !(position.x >= other.position.x + other.width
          || position.x + width <= other.position.x
          || position.y >= other.position.y + other.height
          || position.y + height <= other.position.y);
}

bool Entity::operator==(const Entity &other) {
    return this == &other;
}
