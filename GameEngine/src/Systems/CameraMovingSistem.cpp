#include "Systems/CameraMovingSystem.h"
#include <Components/TransformComponent.h>
#include "../PhysicsEngine/include/ComponentDrop.h"
#include <iostream>


void CameraMovingSystem::OnFixedUpdate() {
	//_camera_location = { 0, 0 };
	const auto& items = _entities->GetEntitiesBy<TransformComponent, ComponentDrop>();

	sf::Vector2f _newLocation = { 0, 0 };

	for (auto& item : items) {
		auto& [currentTransform, currentDrop] = item.Components;
		_newLocation += currentTransform->Location;
	}

	_newLocation /= (float)items.size();
	_newLocation *= -1.f;
	_camera_location = _newLocation;
	//if ()
	//std::cout << " camera x: " << _camera_location.x << " y: " << _camera_location.y << std::endl;
}