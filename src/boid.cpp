#include <SFML/Graphics.hpp>
#include "boid.h"
#include "utils.h"

using namespace sf;

Boid::Boid(Vector2f pos, Color color, float scale) {
    // set up boid shape, like a lil arrow :]
    renderShape.setPointCount(4);
    renderShape.setPoint(0, Vector2f(0, -1));
    renderShape.setPoint(1, Vector2f(-0.7, 1));
    renderShape.setPoint(2, Vector2f(0, 0.7));
    renderShape.setPoint(3, Vector2f(0.7, 1));

    // set shape properties
    renderShape.setPosition(pos);
    renderShape.setFillColor(color);
    renderShape.setScale(scale, scale);

    // initialize physics component
    physics.set_position(pos);
}

void Boid::Update(float delta_time) {
    physics.Update(delta_time);
    renderShape.setPosition(physics.get_position());
}

void Boid::Draw(RenderWindow* window) { window->draw(renderShape); }

void Boid::ApplyForce(Vector2f force) { physics.ApplyForce(force); }
void Boid::ApplyFriction(float coefficient) { physics.ApplyFriction(coefficient); }
Vector2f Boid::get_position() { return physics.get_position(); }

Vector2f Boid::Seek(Vector2f target, float max_speed) {
    Vector2f dir = target - physics.get_position();
    if (dir != Vector2f(0, 0))
        dir = Utils::vec_normalize(dir);
    Vector2f desired_velocity = dir * max_speed;
    return desired_velocity - physics.get_velocity();
}

Vector2f Boid::Flee(Vector2f target, float max_speed) {
    Vector2f dir = physics.get_position() - target;
    if (dir != Vector2f(0, 0))
        dir = Utils::vec_normalize(dir);
    Vector2f desired_velocity = dir * max_speed;
    return desired_velocity - physics.get_velocity();
}
