#include <Components/TransformComponent.h>

#include "utils.h"
#include "DefinesPhysics.h"

#include "Systems/ShiftDropsSystem.h"
#include <iostream>

using namespace sf::Extensions::Vector2;

void ShiftDropsSystem::OnFixedUpdate() {
	int i = 0;//
	const auto& items = _entities
			->GetEntitiesBy<ComponentDrop, TransformComponent, SpeedComponent>();

	for (auto& item : items) {
		auto&[currentDrop, currentTransform, currentSpeed] = item.Components;
		sf::Vector2f _oldLocation = currentTransform->Location;

		currentTransform->Location += currentSpeed->Speed * _gameTime.FixedDeltaTime();

		for (auto& neighbor : currentDrop->neighbours) {
			auto neighborTransform = _entities->GetComponent<TransformComponent>(*neighbor);
			auto neighborSpeed = _entities->GetComponent<SpeedComponent>(*neighbor);
			auto neighborDrop = _entities->GetComponent<ComponentDrop>(*neighbor);

			if (!neighborTransform || !neighborSpeed) continue;

			auto distance = currentTransform->Location->*Magnitude(neighborTransform->Location);
			if (distance < 2 * RADIUS) {
				auto direction = (currentTransform->Location - neighborTransform->Location)->*Normalize();
				/*neighborSpeed->Speed += currentSpeed->Speed * (1.f - SURFACE_FORCE);
				currentSpeed->Speed *= SURFACE_FORCE;*/
				MomentumConservation(*currentSpeed, *neighborSpeed, *neighborDrop);
				currentTransform->Location += direction * (float)(2 * RADIUS - distance);
			}
		}

		// hardcode mood begin

		if (currentTransform->Location.y < -0.19) {
			currentTransform->Location.y = -0.19;
			currentSpeed->Speed.y = 0;
		}

		if (currentTransform->Location.y > 0.83 && currentTransform->Location.x > 0.15 && currentTransform->Location.y < 0.86) {
			currentTransform->Location.y = 0.83;
			currentSpeed->Speed.y = 0;
		}


		if (currentTransform->Location.y > 0.83 && currentTransform->Location.x > 0.15 && currentTransform->Location.x < 0.18) {
			currentTransform->Location.x = 0.15;
			currentSpeed->Speed.x = 0;
		}


		if (currentTransform->Location.x < -0.15 && currentTransform->Location.y > 0.44 && currentTransform->Location.y < 1.15) {
			currentTransform->Location.x = -0.15;
			currentSpeed->Speed.x = 0;
		}


		if (currentTransform->Location.x < -0.88) {
			currentTransform->Location.x = -0.88;
			currentSpeed->Speed.x = 0;
		}

		if (currentTransform->Location.y - 0.75 * currentTransform->Location.x < -0.685) {
			
			currentTransform->Location.y = -0.685 + 0.75 * currentTransform->Location.x;
			currentSpeed->Speed = { 0,0 };
		}

		if (currentTransform->Location.y + 0.63 * currentTransform->Location.x > 1.25 && (currentTransform->Location.x > 0.15 || currentTransform->Location.x < -0.15)) {
			currentTransform->Location.y = 1.25 - 0.63 * currentTransform->Location.x;
			currentSpeed->Speed = { 0,0 };
		}

		if (currentTransform->Location.x > 0.94) {
			currentTransform->Location.x = 0.94;
			currentSpeed->Speed.x = 0;
		}

		if (currentTransform->Location.x < -1 || currentTransform->Location.x > 1.2 || currentTransform->Location.y < -0.3 || currentTransform->Location.x > 1.5) {
			currentTransform->Location = { 0,0 };
			currentSpeed->Speed = { 0,0 };
		}
		
		if ((currentTransform->Location - _oldLocation)->*Length() < (currentSpeed->Speed * _gameTime.FixedDeltaTime())->*Length() - 0.00001f) {
			currentSpeed->Speed -= (_gravitation * _gameTime.FixedDeltaTime()) * 1.5f;  // change
		}

		// hardcode mood end

		//float _wallY = 500; // take from another file
		//float _wallThickness = 2; // take from another file

		//if (currentTransform->Location.y > _wallY - _wallThickness - 2 * RADIUS
		//		&& currentTransform->Location.x < 1000
		//		&& currentTransform->Location.x > 0) {
		//		currentTransform->Location.y = _wallY - _wallThickness - 2 * RADIUS;
		//		currentSpeed->Speed.y = 0;
		//}
	}
}

void ShiftDropsSystem::MomentumConservation(SpeedComponent& currentSpeed, SpeedComponent& neighborSpeed, ComponentDrop& neighborDrop) {
	sf::Vector2f _newSpeed = neighborSpeed.Speed + (currentSpeed.Speed - neighborSpeed.Speed) / (float)(neighborDrop.Volum_Component.Number_Of_Drops + 1);
	ÑhangeSpeed(neighborSpeed, neighborDrop, _newSpeed);
	currentSpeed.Speed = neighborSpeed.Speed;
}

void ShiftDropsSystem::ÑhangeSpeed(SpeedComponent& currentSpeed, ComponentDrop& currentDrop, sf::Vector2f& newSpeed) {
	if (!(currentDrop.if_changed_speed)) {
		currentSpeed.Speed = newSpeed;
		currentDrop.if_changed_speed = true;
			for (auto& neighbor : currentDrop.neighbours) {
				auto neighborSpeed = _entities->GetComponent<SpeedComponent>(*neighbor);
				auto neighborDrop = _entities->GetComponent<ComponentDrop>(*neighbor);
				ÑhangeSpeed(*neighborSpeed, *neighborDrop, newSpeed);
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