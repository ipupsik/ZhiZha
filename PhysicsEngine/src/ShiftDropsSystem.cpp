#include <Components/TransformComponent.h>

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
		sf::Vector2f _oldLocation = currentTransform->Location;

		currentTransform->Location += currentSpeed->Speed * _gameTime.FixedDeltaTime();

		for (auto& neighbor : currentDrop->neighbours) {
			auto neighborTransform = _entities->GetComponent<TransformComponent>(*neighbor);
			auto neighborSpeed = _entities->GetComponent<SpeedComponent>(*neighbor);
			auto neighborDrop = _entities->GetComponent<ComponentDrop>(*neighbor);

			if (!neighborTransform || !neighborSpeed) continue;

			auto distance = currentTransform->Location->*Magnitude(neighborTransform->Location);
			if (distance < 2 * RADIUS && distance >= RADIUS) {
				auto direction = (_oldLocation - neighborTransform->Location)->*Normalize();
				MomentumConservation(*currentSpeed, *neighborSpeed, *neighborDrop);
				currentTransform->Location += direction * (2 * RADIUS);
			} else if (distance < RADIUS) {
				auto direction = sf::Vector2f {0, 1};
				MomentumConservation(*currentSpeed, *neighborSpeed, *neighborDrop);
				currentTransform->Location += direction * (2 * RADIUS);
			}
		}

		// hardcode mood begin
		
		sf::Vector2f _normalVector = { 0, 0 };

		if (currentTransform->Location.y < -0.19) {
			//std::cout << "last y speed: " << currentSpeed->Speed.y << std::endl;
			//currentTransform->Location.y = -0.19;
			_normalVector = { 0, 1 };
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
		if ((currentTransform->Location - _oldLocation)->*Length() < (currentSpeed->Speed * _gameTime.FixedDeltaTime())->*Length() - 0.00001f) {
			currentSpeed->Speed -= (_gravitation * _gameTime.FixedDeltaTime()) * 1.5f;  // change
		}

		// hardcode mood end
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