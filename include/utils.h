#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Utils {
   public:
    static float vec_length(const sf::Vector2f& vector);
    static sf::Vector2f vec_normalize(const sf::Vector2f& vector);
    static Vector2f Utils::vec_clamp(const Vector2f& vector, float max_length);
};
