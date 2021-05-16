
#include "Components.h"
#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class MatInitSystem : public virtual InitSystem {
	sf::Window& _window;

public:
	explicit MatInitSystem(sf::Window& window): _window(window) {}

	void OnPostInit() override;
};