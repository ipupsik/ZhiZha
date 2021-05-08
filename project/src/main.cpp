#include "utils.h"
#include "SystemManager.h"
#include "Systems.h"
#include "SFML/Graphics/RenderWindow.hpp"

using namespace sf::Extensions::Vector2;

int main() {
	auto window = sf::RenderWindow(sf::VideoMode(800, 600), "Sample");

	auto& sys = SystemManager::Current
	            .RegisterSystem<EventSystem>(window)
	            .RegisterSystem<RenderSystem>(window)
	            .RegisterSystem<TestSystem>(TestSystem());

	sys.PostInit();
	while (window.isOpen()) {
		sys.Update();

		sf::Clock clock;
		window.setFramerateLimit(60);
		const auto& time = clock.getElapsedTime();
		sys.PostUpdate();
	}
}
