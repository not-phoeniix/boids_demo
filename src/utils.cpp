#include <SFML/Graphics.hpp>
#include <cmath>
#include "utils.h"

using namespace sf;

float Utils::length(const Vector2f& vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

Vector2f Utils::normalize(const Vector2f& vector) {
    float len = length(vector);
    return Vector2f(vector.x / len, vector.y / len);
}

Vector2f Utils::clamp(const Vector2f& vector, float max_length) {
    float len = length(vector);
    Vector2f return_vec = vector;

    if (len > max_length) {
        return_vec = normalize(vector) * max_length;
    }

    return return_vec;
}
