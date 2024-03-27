#pragma once

#include <SFML/Graphics.hpp>
#include "physics_component.h"

class Boid {
   private:
    sf::ConvexShape renderShape;

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
