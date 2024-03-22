#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main() {
    RenderWindow window(VideoMode(800, 600), "lol!!");
    CircleShape shape(30);
    shape.setFillColor(Color::Red);

    while (window.isOpen()) {
        Event e;

        // poll events every frame
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
        }

        // updates:

        // drawing:
        window.clear(Color::Black);
        window.draw(shape);
        window.display();
    }

    return 0;
}
