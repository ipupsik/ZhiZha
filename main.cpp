#include <iostream>
#include <SFML/Graphics.hpp>

using sf::Window;
using sf::Event;
using sf::VideoMode;

int main() {
    sf::RenderWindow window(VideoMode(1080, 1080 * 9 / 16), "Sample");

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                return 0;
            } else if (event.type == Event::KeyPressed) {
                std::cout << event.key.code << std::endl;
            }
        }
        window.clear(sf::Color::White);
        window.display();
        sf::sleep(sf::seconds(1.f / 60));
    }
}