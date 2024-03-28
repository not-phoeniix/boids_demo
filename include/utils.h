#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Utils {
   public:
    static float vec_length(const sf::Vector2f& vector);
    static float dist(const sf::Vector2f& v1, const sf::Vector2f& v2);
    static float dist_sqr(const sf::Vector2f& v1, const sf::Vector2f& v2);
    static sf::Vector2f vec_normalize(const sf::Vector2f& vector);
    static sf::Vector2f vec_clamp(const sf::Vector2f& vector, float max_length);
};
