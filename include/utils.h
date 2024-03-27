#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Utils {
  public:
    static float length(const sf::Vector2f& vector);
    static sf::Vector2f normalize(const sf::Vector2f& vector);
    static Vector2f Utils::clamp(const Vector2f& vector, float max_length);
};
