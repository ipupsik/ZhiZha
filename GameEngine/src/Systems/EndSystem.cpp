#include <Components/TransformComponent.h>
#include <iostream>
#include "../PhysicsEngine/include/ComponentDrop.h"

#include "../GameEngine/include/Systems/EndSystem.h"

void EndSystem::OnFixedUpdate() {
	//����� ������� ������� -- start
	const auto& items = _entities->GetEntitiesBy<ComponentDrop, TransformComponent>();

	for (auto& [components, current_entity] : items) {
		auto& [drop_current, transformCurrent] = components;
		if (transformCurrent->Location.y > 2) {
			//_entities->DestroyEntity(*current_entity);
		}
	}

	if (items.size() < 500) {
		// std::cout << "you've won!" << std::endl;
	}
	
	if (_time.Time() > 30) {
		// std::cout << "you've lost!" << std::endl;
	}
	//std::cout << items.size() << std::endl;
}
