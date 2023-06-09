#ifndef APACALYPSE_VECTOR_HPP
#define APACALYPSE_VECTOR_HPP

class Vector2f {
public:
    Vector2f(float x = 0.0f, float y = 0.0f);
    friend Vector2f inverse(Vector2f& v);
    friend Vector2f add(Vector2f& v1, Vector2f& v2);
    friend Vector2f add(Vector2f&& v1, Vector2f&& v2);
    friend Vector2f subtract(Vector2f& v1, Vector2f& v2);
    friend Vector2f subtract(Vector2f&& v1, Vector2f&& v2);
    friend Vector2f multiply(Vector2f& v, float multiplier);
    friend Vector2f multiply(Vector2f&& v, float multiplier);
    float getLength() const;
    Vector2f getNormalized() const;
public:
    float x, y;
};

#endif //APACALYPSE_VECTOR_HPP
