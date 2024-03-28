#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "boid.h"
#include "utils.h"

using namespace sf;

int main() {
    RenderWindow window(VideoMode(800, 600), "lol!!");
    Clock delta_clock;
    Time dt;
    window.setFramerateLimit(60);

    RectangleShape viewport_shape;
    viewport_shape.setFillColor(Color::Transparent);
    viewport_shape.setOutlineColor(Color::White);
    viewport_shape.setOutlineThickness(2.0f);

    std::vector<Boid*> boids;

    int num_boids = 100;
    for (int i = 0; i < num_boids; i++) {
        Vector2f pos(rand() % 800, rand() % 600);
        Color color(rand() % 256, rand() % 256, rand() % 256);
        int size = rand() % 5 + 5;
        float view_radius = 50;

        Boid* new_boid = new Boid(pos, color, size, view_radius, boids);

        boids.push_back(new_boid);
    }

    // game loop
    while (window.isOpen()) {
        Event e;

        // poll events every frame
        while (window.pollEvent(e)) {
            // close window upon close event or escape key
            if (e.type == Event::Closed ||
                Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            }

            // dynamically resize window when a resize event is detected
            if (e.type == Event::Resized) {
                FloatRect windowSize(0, 0, e.size.width, e.size.height);
                window.setView(View(windowSize));
            }
        }

        IntRect view_rect(0, 0, window.getSize().x, window.getSize().y);
        view_rect = Utils::modify_rect(view_rect, -50);
        viewport_shape.setPosition((Vector2f)view_rect.getPosition());
        viewport_shape.setSize((Vector2f)view_rect.getSize());
        // viewport_shape.setSize(Vector2f(500, 500));

        // updates:
        dt = delta_clock.restart();
        for (Boid* boid : boids) {
            boid->Update(dt.asSeconds(), view_rect);
        }

        std::cout << "fps: " << (1 / dt.asSeconds()) << "\n";

        // drawing:
        window.clear(Color::Black);
        window.draw(viewport_shape);
        for (Boid* boid : boids) {
            boid->Draw(window);
        }
        window.display();
    }

    // clean up boid memory afterwards
    for (Boid* boid : boids) {
        delete boid;
    }

    boids.clear();

    return 0;
}
