#include <SFML/Graphics.hpp>
#include "boid.h"

using namespace sf;

Boid::Boid(Vector2f pos, Color color, float scale) {
    // set up boid shape, like a lil arrow :]
    this->renderShape.setPointCount(4);
    this->renderShape.setPoint(0, Vector2f(0, -1));
    this->renderShape.setPoint(1, Vector2f(-1, 1));
    this->renderShape.setPoint(2, Vector2f(0, 0.7));
    this->renderShape.setPoint(3, Vector2f(1, 1));

    // set shape properties
    this->renderShape.setPosition(pos);
    this->renderShape.setFillColor(color);
    this->renderShape.setScale(scale, scale);
}

void Boid::Draw(RenderWindow* window) {
    window->draw(this->renderShape);
}
