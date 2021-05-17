#include "CreateComplexCollisionSystem.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Engine.h"
#include "MatInitSystem.h"
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

	auto engine = new Engine(window);
	engine->RegisterSystem<CreateComplexCollisionSystem>(window)
	      .RegisterSystem<MatInitSystem>(window)
	      .RegisterSystem<RenderSystem>(window)
	      .RegisterSystem<EventSystem>(window);
	engine->Start();
}
