#include <SFML/Graphics/RenderWindow.hpp>
#include <Engine.h>
#include "glad/glad.h"

#if defined(linux)
#include <X11/Xlib.h>
#endif

int main() {
#if defined(linux)
    XInitThreads();
#endif
    auto window = sf::RenderWindow(sf::VideoMode(800, 600), "Sample");
    gladLoadGL();

    auto& engine = Engine(window)
        .RegisterSystem<RenderSystem>(RenderSystem(window))
        .RegisterSystem<TestSystem>(TestSystem(0.01));

    engine.Start();
}
