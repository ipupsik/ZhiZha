#include <SFML/Graphics/RenderWindow.hpp>
#include <Engine.h>

#include "Graph.h"

int main() {
    auto window = sf::RenderWindow(sf::VideoMode(800, 600), "Sample");
    auto& engine = Engine(window)
        .RegisterSystem<RenderSystem>(RenderSystem(window))
        .RegisterSystem<TestSystem>(TestSystem(4));

    engine.Start();
}
