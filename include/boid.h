#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "physics_component.h"

class Boid {
   private:
    PhysicsComponent physics;
    sf::ConvexShape render_shape;
    std::vector<Boid*>& container;
    float wander_angle;
    float view_radius;

    // steering behaviors:

    sf::Vector2f Seek(const sf::Vector2f& target);
    sf::Vector2f Seek(Boid& target);
    sf::Vector2f Flee(const sf::Vector2f& target);
    sf::Vector2f Flee(Boid& target);
    sf::Vector2f Wander(float time, float radius);
    sf::Vector2f StayInRect(const sf::IntRect& rectangle);
    sf::Vector2f Separate(float radius);
    sf::Vector2f Cohesion(float radius);
    sf::Vector2f Alignment(float radius);

    sf::Vector2f CalcFuturePos(float time);

   public:
    Boid(sf::Vector2f pos, sf::Color color, float scale, float view_radius, std::vector<Boid*>& container);
    void Update(float delta_time, const sf::IntRect& view_bounds);
    void Draw(sf::RenderWindow& window);

    // getters & setters
    sf::Vector2f get_position();
    sf::Vector2f get_direction();
};
