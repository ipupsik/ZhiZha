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

		sf::Vector2f _normalVector = {0, 0};

		//_columnHeight->*Cos(_gravitation);
		/*if (currentSpeed->Speed.y < 0.000005) {
			
		}*/

		if (currentTransform->Location.y < -0.19) { // низ
			//std::cout << "last y speed: " << currentSpeed->Speed.y << std::endl;
			//currentTransform->Location.y = -0.19;
			_normalVector = { 0, 1 };

			//currentSpeed->Speed -= currentSpeed->Speed;
			
			/*currentSpeed->Speed += _normalVector ;
			currentSpeed->Speed *= 0.4f;*/
			//currentSpeed->Speed.y = 0;
			//std::cout << " y speed: " << currentSpeed->Speed.y << std::endl << "------------" << std::endl;
		}

		if (currentTransform->Location.y > 0.83 && currentTransform->Location.x > 0.15 && currentTransform->Location.y < 0.86) { // верх
			//currentTransform->Location.y = 0.83;
			_normalVector = { 0, -1 };
			//currentSpeed->Speed.y = 0;
		}


		if (currentTransform->Location.y > 0.83 && currentTransform->Location.x > 0.15 && currentTransform->Location.x < 0.18) { // верх право
			//currentTransform->Location.x = 0.15;
			_normalVector = { -1, 0 };
			//currentSpeed->Speed.x = 0;
		}


		if (currentTransform->Location.x < -0.15 && currentTransform->Location.y > 0.44 && currentTransform->Location.y < 1.15) { // перегородка
			//currentTransform->Location.x = -0.15;
			_normalVector = { 1, 0 };
			//currentSpeed->Speed.x = 0;
		}

		if (currentTransform->Location.x < -0.88) {  // левая стенка
			//currentTransform->Location.x = -0.88;
			_normalVector = { 1, 0 };
			//currentSpeed->Speed.x = 0;
		}

		if (currentTransform->Location.y - 0.75 * currentTransform->Location.x < -0.685) { // нижний треугольник 
			//currentTransform->Location.y = -0.685 + 0.75 * currentTransform->Location.x;
			_normalVector = { -0.6, 0.8 };

			//currentSpeed->Speed = { 0,0 };
		}

		if (currentTransform->Location.y + 0.63 * currentTransform->Location.x > 1.25 && (currentTransform->Location.x > 0.15 || currentTransform->Location.x < -0.15)) {  // верхний треугольник
			//currentTransform->Location.y = 1.25 - 0.63 * currentTransform->Location.x;
			//currentSpeed->Speed = { 0,0 };
		}

		if (currentTransform->Location.x > 0.94) { // вравая стенка
			_normalVector = { -1, 0 };
			//currentTransform->Location.x = 0.94;
			//currentSpeed->Speed.x = 0;
		}

		if (currentTransform->Location.x < -1 || currentTransform->Location.x > 1.2 || currentTransform->Location.y < -0.3 || currentTransform->Location.x > 1.5) {
			currentTransform->Location = { 0,0 };
			currentSpeed->Speed = { 0,0 };
		}

		if (_normalVector->*Length() > 0.00001) {
			_normalVector = _normalVector->*RotateRad(PI / 2);
			currentSpeed->Speed.y = 0;
			currentTransform->Location = _oldLocation;

			_normalVector *= currentSpeed->Speed->*Length();
			_normalVector *= _normalVector->*Cos(currentSpeed->Speed);
			currentSpeed->Speed = { 0, 0 };
			currentSpeed->Speed += _normalVector;
		}
/*
		_normalVector *= currentSpeed->Speed->*Length();

		if (_normalVector->*Length() > 0.000001) {
			_normalVector *= _normalVector->*Sin(currentSpeed->Speed);
			currentSpeed->Speed = { 0, 0 };
			currentSpeed->Speed += _normalVector;
			currentSpeed->Speed *= 1.0f;
		}/*
		//std::cout << " _normalVector y: " << _normalVector.y << std::endl << "------------" << std::endl;
		
		

		//currentSpeed->Speed += _normalVector;
		/*if (abs(_normalVector->*Length() - 1) > 0.0001) {
			std::cout << "_ " << _normalVector.y << std::endl;
			currentSpeed->Speed *= 0.4f;
		}*/
		//currentSpeed->Speed *= 0.4f;

		// hardcode mood end

		//float _wallY = 500; // take from another file
		//float _wallThickness = 2; // take from another file

		//if (currentTransform->Location.y > _wallY - _wallThickness - 2 * RADIUS
		//		&& currentTransform->Location.x < 1000
		//		&& currentTransform->Location.x > 0) {
		//		currentTransform->Location.y = _wallY - _wallThickness - 2 * RADIUS;
		//		currentSpeed->Speed.y = 0;
		//}

		if ((currentTransform->Location - _oldLocation)->*Length() < (currentSpeed->Speed * _gameTime.FixedDeltaTime())->*Length() - 0.00001f) {
			currentSpeed->Speed -= (_gravitation * _gameTime.FixedDeltaTime()) * 1.5f;  // change
		}
	}
}

void ShiftDropsSystem::MomentumConservation(SpeedComponent& currentSpeed, SpeedComponent& neighborSpeed, ComponentDrop& neighborDrop) {
	sf::Vector2f _newSpeed = neighborSpeed.Speed + (currentSpeed.Speed - neighborSpeed.Speed) / (float)(neighborDrop.Volum_Component.Number_Of_Drops + 1);
	ChangeSpeed(neighborSpeed, neighborDrop, _newSpeed);
	currentSpeed.Speed = neighborSpeed.Speed;
}

void ShiftDropsSystem::ChangeSpeed(SpeedComponent& currentSpeed, ComponentDrop& currentDrop, sf::Vector2f& newSpeed) {
	if (!(currentDrop.if_changed_speed)) {
		currentSpeed.Speed = newSpeed;
		currentDrop.if_changed_speed = true;
			for (auto& neighbor : currentDrop.neighbours) {
				auto neighborSpeed = _entities->GetComponent<SpeedComponent>(*neighbor);
				auto neighborDrop = _entities->GetComponent<ComponentDrop>(*neighbor);
				ChangeSpeed(*neighborSpeed, *neighborDrop, newSpeed);
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