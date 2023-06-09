#include <cmath>
#include "../include/vector.hpp"

Vector2f::Vector2f(float x, float y) : x(x), y(y) {
}

Vector2f inverse(Vector2f& v) {
    return {-v.x, -v.y};
}

Vector2f add(Vector2f& v1, Vector2f& v2) {
    return {v1.x + v2.x, v1.y + v2.y};
}

Vector2f add(Vector2f &&v1, Vector2f &&v2) {
    return {v1.x + v2.x, v1.y + v2.y};;
}

Vector2f subtract(Vector2f& v1, Vector2f& v2) {
    return {v1.x - v2.x, v1.y - v2.y};
}

Vector2f subtract(Vector2f &&v1, Vector2f &&v2) {
    return {v1.x - v2.x, v1.y - v2.y};
}

Vector2f multiply(Vector2f &v, float multiplier) {
    return Vector2f(v.x * multiplier, v.y * multiplier);
}

Vector2f multiply(Vector2f &&v, float multiplier) {
    return Vector2f(v.x * multiplier, v.y * multiplier);
}

float Vector2f::getLength() const {
    return sqrt(pow(x, 2) + pow(y, 2));
}

Vector2f Vector2f::getNormalized() const {
    return {x / getLength(), y / getLength()};
}
