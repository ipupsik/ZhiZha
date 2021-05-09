#include "Components.h"
#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class TestSystem : public virtual System<TestSystem>, public virtual FixedUpdateSystem {
	sf::Uint8 _step;
	sf::Color _latestColor = sf::Color::White;
	Entity _canvas;

public:
	TestSystem(const sf::Uint8 step): _step(step),
	                                                            _canvas(_entities.CreateEntity()) {
		_entities.GetOrAddComponent<RenderComponent>(_canvas);
		_entities.GetOrAddComponent<NameComponent>(_canvas, [](NameComponent& item) {
			item.Name = "Canvas";
		});
	}

	void OnFixedUpdate() override;
};

class EventSystem : public virtual System<EventSystem>, public virtual PostInitSystem {
	sf::RenderWindow& _window;

public:
	explicit EventSystem(sf::RenderWindow& window): _window(window) {}

	void OnPostInit() override;
};

class RenderSystem : public virtual System<RenderSystem>, public virtual PostUpdateSystem {
	sf::RenderWindow& _window;

public:
	explicit RenderSystem(sf::RenderWindow& window): _window(window) {}

	void OnPostUpdate() override;
};
