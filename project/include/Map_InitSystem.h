#include "Components/Components.h"
#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class Map_InitSystem : public virtual InitSystem {
	sf::Window& _window;

public:
	explicit Map_InitSystem(sf::Window& window) : _window(window) {}

	void OnInit() override;
};