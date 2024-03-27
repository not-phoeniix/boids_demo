#pragma once

#include <SFML/Graphics.hpp>
#include "physics_component.h"

class Boid {
   private:
    sf::ConvexShape renderShape;
    sf::Vector2f Seek(sf::Vector2f target, float max_speed);
    sf::Vector2f Flee(sf::Vector2f target, float max_speed);

   public:
    Boid(sf::Vector2f pos, sf::Color color, float scale);
    void Update(float delta_time);
    void Draw(sf::RenderWindow* window);
    void ApplyForce(sf::Vector2f force);
    void ApplyFriction(float coefficient);
    PhysicsComponent physics;

    // getters & setters
    sf::Vector2f get_position();
};
