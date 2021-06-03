#include <Components/TransformComponent.h>
#include <iostream>
#include "../PhysicsEngine/include/ComponentDrop.h"

#include "../GameEngine/include/Systems/EndSystem.h"

void EndSystem::OnFixedUpdate() {
	//����� ������� ������� -- start
	const auto& items = _entities->GetEntitiesBy<ComponentDrop, TransformComponent>();

	for (auto& [components, current_entity] : items) {
		auto& [drop_current, transformCurrent] = components;
		if (transformCurrent->Location.y > 1) {
			_entities->DestroyEntity(*current_entity);
		}
	}
	
	if (_engine.GetTime().Time() > 40 && !_isOver) {
		_isOver = true;
		_engine.UnloadScene();
		_engine.LoadScene(Scene::End);
		// std::cout << "you've lost!" << std::endl;
	}
	//std::cout << items.size() << std::endl;
}
