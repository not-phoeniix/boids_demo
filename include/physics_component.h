#pragma once

#include <SFML/Graphics.hpp>

class PhysicsComponent {
   private:
    float mass;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

   public:
    PhysicsComponent(sf::Vector2f position, float mass);
    PhysicsComponent();

    // methods
    void Update(float delta_time);
    void ApplyForce(sf::Vector2f force);
    void ApplyFriction(float coefficient);

    // getters & setters
    sf::Vector2f get_position();
    sf::Vector2f get_velocity();
    sf::Vector2f get_acceleration();
    void set_position(sf::Vector2f pos);
    void set_mass(float mass);
};
