#include <SFML/Graphics.hpp>
#include "boid.h"

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

void Boid::Draw(RenderWindow* window) {
    window->draw(renderShape);
}

void Boid::ApplyForce(Vector2f force) { physics.ApplyForce(force); }
void Boid::ApplyFriction(float coefficient) { physics.ApplyFriction(coefficient); }
Vector2f Boid::get_position() { return physics.get_position(); }
