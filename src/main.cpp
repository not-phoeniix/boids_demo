#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "boid.h"
#include "bsp.h"
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

    BSPNode node(IntRect(0, 0, 800, 600), 50);

    int num_boids = 300;
    for (int i = 0; i < num_boids; i++) {
        Vector2f pos(rand() % 800, rand() % 600);
        Color color(rand() % 256, rand() % 256, rand() % 256);
        int size = rand() % 5 + 5;
        float view_radius = 60;

        Boid* new_boid = new Boid(pos, color, size, view_radius);

        // boids.push_back(new_boid);
        node.Add(new_boid);
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

        // updates:
        dt = delta_clock.restart();
        node.Update(dt.asSeconds(), view_rect);

        // drawing:
        window.clear(Color::Black);
        window.draw(viewport_shape);
        node.Draw(window);
        node.DrawBounds(window);
        window.display();

        // std::cout << "fps: " << (1 / dt.asSeconds()) << "\n";
    }

    return 0;
}
