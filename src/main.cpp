#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "boid.h"

using namespace sf;

int main() {
    RenderWindow window(VideoMode(800, 600), "lol!!");
    Clock delta_clock;
    Time dt;
    window.setFramerateLimit(60);

    std::vector<Boid*> boids;

    int num_boids = 10;
    for (int i = 0; i < num_boids; i++) {
        Boid* new_boid = new Boid(
            Vector2f(rand() % 800, rand() % 600),
            Color::Red,
            (rand() % 11) + 10  // value from 10-20
        );

        boids.push_back(new_boid);
    }

    // game loop
    while (window.isOpen()) {
        Event e;

        // poll events every frame
        while (window.pollEvent(e)) {
            // close window upon close event or escape key
            if (e.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            }

            // dynamically resize window when a resize event is detected
            if (e.type == Event::Resized) {
                FloatRect windowSize(0, 0, e.size.width, e.size.height);
                window.setView(View(windowSize));
            }
        }

        // updates:
        dt = delta_clock.restart();
        for (Boid* boid : boids) {
            boid->ApplyForce(Vector2f(0, -50));
            boid->Update(dt.asSeconds());
        }

        // drawing:
        window.clear(Color::Black);
        for (Boid* boid : boids) {
            boid->Draw(&window);
        }
        window.display();
    }

    // clean up boid memory afterwards
    for (Boid* boid : boids) {
        delete boid;
    }

    return 0;
}
