#pragma once

#include <SFML/Graphics.hpp>

class Boid {
   private:
    sf::Vector2f position;
    sf::ConvexShape renderShape;

   public:
    Boid(sf::Vector2f pos, sf::Color color, float scale);
    void Draw(sf::RenderWindow* window);
    void Update(float deltaTime);
};
