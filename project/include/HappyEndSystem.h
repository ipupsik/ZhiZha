#include "System.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <ResourceManager.h>

class HappyEndSystem: public virtual InitSystem,
					  public virtual UpdateSystem,
					  public virtual UnloadSystem {
	sf::RenderWindow& _window;
	ResourceManager& _resources;
	std::vector<Entity*> _createdEntities;
	sf::Text _gameOver;

public:
	HappyEndSystem(sf::RenderWindow& window, ResourceManager& resources)
			:_window(window), _resources(resources) { }

	void OnUpdate() override;
	void OnInit() override;
	void OnSceneUnload(Scene scene) override;
};