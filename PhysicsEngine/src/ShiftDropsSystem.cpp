#include <Components/TransformComponent.h>

#include "ComponentDrop.h"
#include "ComponentVolume.h"
#include "Components/SpeedComponent.h"
#include "utils.h"
#include "DefinesPhysics.h"

#include "Systems/ShiftDropsSystem.h"
#include <iostream>

using namespace sf::Extensions::Vector2;

void ShiftDropsSystem::OnFixedUpdate() {
	const auto& items = _entities
			->GetEntitiesBy<ComponentDrop, TransformComponent, SpeedComponent>();

	for (auto& item : items) {
		auto&[currentDrop, currentTransform, currentSpeed] = item.Components;
		currentTransform->Location += currentSpeed->Speed * _gameTime.FixedDeltaTime();

		for (auto& neighbor : currentDrop->neighbours) {
			auto neighborTransform = _entities->GetComponent<TransformComponent>(*neighbor);
			auto neighborSpeed = _entities->GetComponent<SpeedComponent>(*neighbor);

			if (!neighborTransform || !neighborSpeed) continue;

			auto distance = currentTransform->Location->*Magnitude(neighborTransform->Location);
			if (distance < 2 * RADIUS) {
				auto direction = (currentTransform->Location - neighborTransform->Location)->*Normalize();
				neighborSpeed->Speed += currentSpeed->Speed * (1.f - SURFACE_FORCE);
				currentSpeed->Speed *= SURFACE_FORCE;
				currentTransform->Location += (2 * RADIUS - distance) * direction;
			}
		}

		float _wallY = 500; // take from another file
		float _wallThickness = 2; // take from another file

		if (currentTransform->Location.y > _wallY - _wallThickness - 2 * RADIUS
				&& currentTransform->Location.x < 1000
				&& currentTransform->Location.x > 0) {
				currentTransform->Location.y = _wallY - _wallThickness - 2 * RADIUS;
				currentSpeed->Speed.y = 0;
			}
	}
}
//
//			auto& current_drop_comp = *(_entities->GetComponent<ComponentDrop>(*current_drop));
//
//			float _wallY = 500; // take from another file
//			float _wallThickness = 2; // take from another file
//
//			if (neighborTransform->Location.y > _wallY - _wallThickness - 2 * RADIUS
//				&& neighborTransform->Location.x < 1000
//				&& neighborTransform->Location.x > 0) {
////				current_drop_transform->Location.y = _wallY - _wallThickness - 2 * RADIUS;
//				neighborSpeed.Speed.y = 0;
//				currentDrop->Is_Interract_Wall = true;
//			}
//
//			for (auto neighbour : current_drop_comp.neighbours) {
//				auto& other_drop_comp = *(_entities->GetComponent<ComponentDrop>(*neighbour));
//				if (!(other_drop_comp.is_moved) && !(other_drop_comp.is_in_queue))
//				{
//					other_drop_comp.is_in_queue = true;
//					currentDrop->Perimetr_drops.push(neighbour);
//				}
//			}
//
//			current_drop_comp.is_in_queue = false;
//			currentDrop->Perimetr_drops.pop();