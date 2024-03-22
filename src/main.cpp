#include <iostream>
#include <SFML/Graphics.hpp>
#include "boid.h"

using namespace sf;

int main() {
    RenderWindow window(VideoMode(800, 600), "lol!!");
    Clock deltaClock;
    Time deltaTime;
	Boid boidSilly(Vector2f(400, 300), Color::Red, 20);

    while (window.isOpen()) {
        Event e;

        // poll events every frame
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        // updates:
        deltaTime = deltaClock.restart();

        // drawing:
        window.clear(Color::Black);
		boidSilly.Draw(&window);
        window.display();
    }

    return 0;
}
