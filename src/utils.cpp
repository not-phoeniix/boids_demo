#include <SFML/Graphics.hpp>
#include <cmath>
#include "utils.h"

using namespace sf;

float Utils::vec_length(const Vector2f& vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float Utils::dist(const Vector2f& v1, const Vector2f& v2) {
    return sqrt(
        (v2.x - v1.x) * (v2.x - v2.x) +
        (v2.y - v1.y) * (v2.y - v1.y)
    );
}

float Utils::dist_sqr(const Vector2f& v1, const Vector2f& v2) {
    return (v2.x - v1.x) * (v2.x - v2.x) +
           (v2.y - v1.y) * (v2.y - v1.y);
}

Vector2f Utils::vec_normalize(const Vector2f& vector) {
    float len = vec_length(vector);
    return Vector2f(vector.x / len, vector.y / len);
}

Vector2f Utils::vec_clamp(const Vector2f& vector, float max_length) {
    float len = vec_length(vector);
    Vector2f return_vec = vector;

    if (len > max_length) {
        return_vec = vec_normalize(vector) * max_length;
    }

    return return_vec;
}
