#pragma once

#include <SFML/Graphics.hpp>

class PhysicsComponent {
   private:
    float mass;
    float max_speed;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

   public:
    PhysicsComponent(sf::Vector2f position, float mass, float max_speed);
    PhysicsComponent();

    // methods
    void Update(float delta_time);
    void ApplyForce(sf::Vector2f force);
    void ApplyFriction(float coefficient);

    // getters & setters
    sf::Vector2f get_position();
    sf::Vector2f get_velocity();
    sf::Vector2f get_acceleration();
    sf::Vector2f get_direction();
    float get_max_speed();
    void set_position(const sf::Vector2f& pos);
    void set_mass(float mass);
    void set_max_speed(float max_speed);
};
