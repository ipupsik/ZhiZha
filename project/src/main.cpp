#include <Systems/RenderSystem.h>
#include <Systems/MoveSystem.h>
#include "Systems/CreateComplexCollisionSystem.h"
#include "Map_InitSystem.h"
#include "Engine.h"
#include "glad/glad.h"
#include "Systems/EventSystem.h"
#include "Systems/FPSSystem.h"

#if defined(linux)
#include <X11/Xlib.h>
#endif

int main() {
#if defined(linux)
	XInitThreads();
#endif
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	auto window = sf::RenderWindow(sf::VideoMode(1080, 720), "Sample", sf::Style::Default,
			settings);

	gladLoadGL();

	auto engine = new Engine(window);
	engine->RegisterSystem<Map_InitSystem>(engine->GetResourceManager())
			.RegisterSystem<CreateComplexCollisionSystem>(window)
			.RegisterSystem<EventSystem>(window)
			.RegisterSystem<RenderSystem>(window)
			.RegisterSystem<FPSSystem>(engine->GetTime(), window, engine->GetResourceManager())
			.RegisterSystem<MoveSystem>( engine->GetTime());
	engine->Start();
}
