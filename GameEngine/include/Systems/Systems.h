#include "Components/Components.h"
#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

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