#include <iostream>
#include <SFML/Graphics.hpp>
#include "physics_component.h"
#include "utils.h"

using namespace sf;

PhysicsComponent::PhysicsComponent(Vector2f position, float mass, float max_speed)
: position(position), mass(mass), max_speed(max_speed) { }

PhysicsComponent::PhysicsComponent() : PhysicsComponent(Vector2f(0, 0), 1.0f, 1000.0f) { }

void PhysicsComponent::Update(float delta_time) {
    velocity += acceleration * delta_time;
    position += velocity * delta_time;
    acceleration = Vector2f(0, 0);
}

void PhysicsComponent::ApplyForce(Vector2f force) {
    force /= mass;
    acceleration += force;
}

void PhysicsComponent::ApplyFriction(float coefficient) {
    if (velocity != Vector2f(0, 0)) {
        // make this normalize, forgot to make a normalizing functon lol
        Vector2f friction(0, 0);
        ApplyForce(friction);
    }
}

// getters & setters
Vector2f PhysicsComponent::get_position() { return position; }
Vector2f PhysicsComponent::get_velocity() { return velocity; }
Vector2f PhysicsComponent::get_acceleration() { return acceleration; }
Vector2f PhysicsComponent::get_direction() {
    if (velocity == Vector2f(0, 0)) {
        return Vector2f(0, 0);
    } else {
        return Utils::vec_normalize(velocity);
    }
}
float PhysicsComponent::get_max_speed() { return max_speed; }
void PhysicsComponent::set_position(Vector2f pos) { position = pos; }
void PhysicsComponent::set_mass(float mass) { this->mass = mass; }
void PhysicsComponent::set_max_speed(float max_speed) { this->max_speed = max_speed; }
