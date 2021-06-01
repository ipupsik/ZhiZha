#include "Systems/CameraMovingSystem.h"
#include <Components/TransformComponent.h>
#include "../PhysicsEngine/include/ComponentDrop.h"
//#include <iostream>


void CameraMovingSystem::OnFixedUpdate() {
	//_camera_location = { 0, 0 };
	const auto& items = _entities->GetEntitiesBy<TransformComponent, ComponentDrop>();

	if (items.empty())
		return;

	sf::Vector2f _newLocation = { 0, 0 };
	int good_count = 0;
	for (auto& item : items) {
		auto&[currentTransform, currentDrop] = item.Components;
		sf::Vector2f screen_location = currentTransform->Location - _camera_location;
		if (screen_location.x <= 2.6f && screen_location.x >= -2.6f)
			if (screen_location.y <= 2.6f && screen_location.y >= -2.6f) {
				_newLocation += currentTransform->Location;
				good_count++;
			}
	}
	if (good_count > 0) {
		_newLocation /= (float)good_count;
		_newLocation *= -1.f;
		_camera_location = (_camera_location + _newLocation) * (1 / 2.f);
	}

	//std::cout << " camera x: " << _camera_location.x << " y: " << _camera_location.y << std::endl;
}