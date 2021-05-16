
#include "Components.h"
#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class CreateComplexCollisionSystem : public virtual PostInitSystem {
	sf::Window& _window;

public:
	explicit CreateComplexCollisionSystem(sf::Window& window): _window(window) {}

	void OnPostInit() override;
};