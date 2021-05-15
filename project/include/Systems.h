#include "Components.h"
#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class TestSystem : public virtual FixedUpdateSystem {
	double _step;
	double _x = 0;
	Entity _canvas;

public:
	TestSystem(const double step): _step(step), _canvas(_entities.CreateEntity()) {
		_entities.GetOrAddComponent<RenderComponent>(_canvas);
		_entities.GetOrAddComponent<NameComponent>(_canvas, [](NameComponent& item) {
			item.Name = "Canvas";
		});
	}

	void OnFixedUpdate() override;
};

/**
 * Эта система используется для обработки связанной с окном: передвинули мышку, растянули окно или
 * нажали кнопку.
 */
class EventSystem : public virtual PostInitSystem {
	sf::Window& _window;

public:
	explicit EventSystem(sf::Window& window): _window(window) {}

	void OnPostInit() override;
};

class RenderSystem : public virtual PostUpdateSystem {
	sf::RenderWindow& _window;

public:
	explicit RenderSystem(sf::RenderWindow& window): _window(window) {}

	void OnPostUpdate() override;
};

class HugeSystem: public virtual InitSystem, public virtual UpdateSystem {
	std::size_t _count;

public:
	explicit HugeSystem(std::size_t count): _count(count) {}

	void OnUpdate() override;
	void OnInit() override;
};