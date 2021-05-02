#include <iostream>
#include <SFML/Window.hpp>

using sf::Window;
using sf::Event;
using sf::VideoMode;

int main() {
    auto window = Window(VideoMode(1080, 1080 * 9 / 16), "Sample");
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed)
                std::cout << event.key.code << std::endl;
        }
    }
}