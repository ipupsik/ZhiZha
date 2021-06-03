#include "Systems/CameraMovingSystem.h"
#include <Components/TransformComponent.h>
#include "../PhysicsEngine/include/ComponentDrop.h"
#include <iostream>


void CameraMovingSystem::OnFixedUpdate() {
	//_camera_location = { 0, 0 };
	const auto& items = _entities->GetEntitiesBy<TransformComponent, ComponentDrop>();

	sf::Vector2f _newLocation = { 0, 0 };
	int good_count = 0;
	for (auto& item : items) {
		auto&[currentTransform, currentDrop] = item.Components;
		sf::Vector2f screen_location = currentTransform->Location - _camera_location;
		if (screen_location.x <= 100.f && screen_location.x >= -100.f)
			if (screen_location.y <= 100.f && screen_location.y >= -100.f) {
				_newLocation += currentTransform->Location;
				good_count++;
			}
	}

	if (good_count > 0) {
		_newLocation /= (float)good_count;
		_newLocation *= -1.f;
		_camera_location = (_camera_location + _newLocation) * (1 / 2.f);
		for (auto& [components, current_entity] : items) {
			auto& [currentTransform, currentDrop] = components;
			if (abs(currentTransform->Location.x + _camera_location.x) > 1.5f ||
				abs(currentTransform->Location.y + _camera_location.y) > 1.5f) {
				_entities->DestroyEntity(*current_entity);
				//std::cout << " camera x: " << _camera_location.x << " y: " << _camera_location.y << std::endl;
				//std::cout << " currentTransform x: " << currentTransform->Location.x << " currentTransform y: " << currentTransform->Location.y << std::endl;
				//system("pause");
			}
		}
	}
	

	
}