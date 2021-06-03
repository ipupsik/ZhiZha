#include <Components/TransformComponent.h>
#include <iostream>
#include <stdlib.h> 
#include "../PhysicsEngine/include/ComponentDrop.h"

#include "../GameEngine/include/Systems/EndSystem.h"

void EndSystem::OnFixedUpdate() {
	//����� ������� ������� -- start
	const auto& items = _entities->GetEntitiesBy<ComponentDrop, TransformComponent>();
	for (auto& [components, current_entity] : items) {
		auto& [drop_current, transformCurrent] = components;
		if (transformCurrent->Location.x > 6.35) {
			transformCurrent->Scale = { 0.03, 0.03 };
		}
		if (transformCurrent->Location.x > 6.4 && (transformCurrent->Location.y > 4.4 && transformCurrent->Location.y < 4.87)) {
			_entities->DestroyEntity(*current_entity);
			std::cout << " Win" << std::endl;
		}
	}

	if (items.size() == 0) {
		// Lose
	}
	
	if (_engine.GetTime().Time() > 70 && !_isOver) {
		_isOver = true;
		_engine.UnloadScene();
		_engine.LoadScene(Scene::End);
		// std::cout << "you've lost!" << std::endl;
	}
	//std::cout << items.size() << std::endl;
}
