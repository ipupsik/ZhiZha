
#include "Components.h"
#include "System.h"
#include "SFML/Graphics/RenderWindow.hpp"

class CollisionSystem : public virtual FixedUpdateSystem {
	sf::Window& _window;

public:
	explicit CollisionSystem(sf::Window& window): _window(window) {}

	void OnFixedUpdate() override;
};