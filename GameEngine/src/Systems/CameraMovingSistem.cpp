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

	for (auto& item : items) {
		auto& [currentTransform, currentDrop] = item.Components;
		sf::Vector2f screen_location = currentTransform->Location - _camera_location;
		if (screen_location.x <= 1.4f && screen_location.x >= -1.4f)
			if (screen_location.y <= 1.4f && screen_location.y >= -1.4f)
				_newLocation += currentTransform->Location;
	}
	if (items.size() > 0)
	{
		_newLocation /= (float)items.size();
		_newLocation *= -1.f;
		_camera_location = _newLocation;
	}
	
	if (_newLocation.x != _newLocation.x){
		_camera_location = { 0,0 };
	}
	//std::cout << " camera x: " << _camera_location.x << " y: " << _camera_location.y << std::endl;
}