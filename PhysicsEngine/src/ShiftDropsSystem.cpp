#include <Components/TransformComponent.h>
#include "Components/ComplexCollisionComponent.h"

#include "utils.h"
#include "DefinesPhysics.h"
#include "Components/MeshComponent.h"
#include "Components/MeshCollider.h"


#include "Systems/ShiftDropsSystem.h"
#include "math.h"
#include <iostream>

using namespace sf::Extensions::Vector2;

void ShiftDropsSystem::OnFixedUpdate() {
	const auto& items = _entities
			->GetEntitiesBy<ComponentDrop, TransformComponent, SpeedComponent>();
	const auto& maps_items = _entities->GetEntitiesBy<ComplexCollisionComponent>();

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
			}
			else if (distance < RADIUS) {
				auto direction = sf::Vector2f{ 0, 1 };
				MomentumConservation(*currentSpeed, *neighborSpeed, *neighborDrop);
				currentTransform->Location += direction * (2 * RADIUS);
			}
		}

		for (auto& [components_map, cur_map_item] : maps_items)
		{
			auto& [ccc] = components_map;

			//std::cout << ccc->ComplexCollision.size() << std::endl;

			for (int i = 0; i < ccc->ComplexCollision.size(); ++i)
			{
				// составление векторов-сторон треугольника
				sf::Vector2f vec12 = ccc->ComplexCollision[i].v2 - ccc->ComplexCollision[i].v1;
				sf::Vector2f vec13 = ccc->ComplexCollision[i].v3 - ccc->ComplexCollision[i].v1;
				sf::Vector2f vec23 = ccc->ComplexCollision[i].v3 - ccc->ComplexCollision[i].v2;

				// составление вектора от каждой точки до центра окружности
				sf::Vector2f vec10 = currentTransform->Location - ccc->ComplexCollision[i].v1;
				sf::Vector2f vec20 = currentTransform->Location - ccc->ComplexCollision[i].v2;
				sf::Vector2f vec30 = currentTransform->Location - ccc->ComplexCollision[i].v3;

				//// Erema

				/*vec01 = { 1,0 };
				vec02 = { -0.5, 0.866025 };
				vec03 = { -0.5, -0.866025 };*/

				/*std::cout << "acos(_cos12): " << acos(_cos12) * 180 / PI << std::endl;
				std::cout << "acos(_cos13): " << acos(_cos13) * 180 / PI << std::endl;
				std::cout << "acos(_cos23): " << acos(_cos23) * 180 / PI << std::endl;*/


				/*if (abs((acos(_cos12) + acos(_cos13) + acos(_cos23) - 2 * PI)) < 0.0001) {
					std::cout << "--------------" << std::endl;
					system("pause");
				 }*/
				//// Erema



				float cos_012 = vec12->*Dot(vec10) / vec12->*Length() / vec10->*Length();

				float cos_021 = (-vec12)->*Dot(vec20) / vec12->*Length() / vec20->*Length();

				float cos_013 = vec13->*Dot(vec10) / vec13->*Length() / vec10->*Length();
				float cos_031 = (-vec13)->*Dot(vec30) / vec13->*Length() / vec30->*Length();


				float cos_023 = vec23->*Dot(vec20) / vec23->*Length() / vec20->*Length();
				float cos_032 = (-vec23)->*Dot(vec30) / vec23->*Length() / vec30->*Length();

				float h_12 = fabs(sqrt(pow(vec10->*Length(), 2) - pow(cos_012 * vec10->*Length(), 2)));
				float h_13 = fabs(sqrt(pow(vec10->*Length(), 2) - pow(cos_013 * vec10->*Length(), 2)));
				float h_23 = fabs(sqrt(pow(vec20->*Length(), 2) - pow(cos_023 * vec20->*Length(), 2)));

				float min_h; //минимальное расстояние до стороны
				sf::Vector2f min_line; //минимальная сторона
				sf::Vector2f min_dist_to_center; //минимальное расстояние до центра окружности
				bool does_hit = false;

				if (cos_012 >= 0 && cos_021 >= 0)
				{
					min_h = h_12;
					min_line = vec12;
					min_dist_to_center = vec10;

					does_hit = true;
				}
				else if (cos_012 < 0 && cos_021 >= 0)
				{
					min_h = vec10->*Length();
					min_line = vec12;
					min_dist_to_center = vec10;

					does_hit = true;
				}

				if (cos_013 >= 0 && cos_031 >= 0)
				{
					if (!does_hit || h_13 < min_h)
					{
						min_h = h_13;
						min_line = vec13;
						min_dist_to_center = vec10;

						does_hit = true;
					}
				}
				else if (cos_013 < 0 && cos_031 >= 0)
				{
					if (!does_hit || vec10->*Length() < min_h)
					{
						min_h = vec10->*Length();
						min_line = vec13;
						min_dist_to_center = vec10;

						does_hit = true;
					}
				}

				if (cos_023 >= 0 && cos_032 >= 0)
				{
					if (!does_hit || h_23 < min_h)
					{
						min_h = h_23;
						min_line = vec23;
						min_dist_to_center = vec20;

						does_hit = true;
					}
				}
				else if (cos_023 < 0 && cos_032 >= 0)
				{
					if (!does_hit || vec20->*Length() < min_h)
					{
						min_h = vec20->*Length();
						min_line = vec23;
						min_dist_to_center = vec20;

						does_hit = true;
					}
				}

				// int res = min_h < RADIUS;
				//std::cout << "hello" << std::endl;

				if (does_hit && min_h < RADIUS)
				{
					//std::cout << "collided wall" << std::endl;

					float z_coord = -min_line.x * min_dist_to_center.y + min_line.y * min_dist_to_center.x;
					sf::Vector2f _normalVector = {
						min_line.y * z_coord,
						-min_line.x * z_coord
					};

					_normalVector = _normalVector->*Normalize();
					//_normalVector *= -1.f;

					/*std::cout << "x: " << _normalVector.x << " y: " << _normalVector.y << std::endl;
					std::cout << "current location x: " << currentTransform->Location.x << " current location y: " << currentTransform->Location.y << std::endl;
					std::cout << "_oldLocation x: " << _oldLocation.x << " _oldLocation y: " << _oldLocation.y << std::endl << std::endl;
					*/
					
					
					currentTransform->Location = _oldLocation;

					_normalVector = _normalVector->*RotateRad(PI / 2);


					_normalVector *= currentSpeed->Speed->*Length();
					_normalVector *= _normalVector->*Cos(currentSpeed->Speed);
					currentSpeed->Speed = { 0, 0 };
					currentSpeed->Speed += _normalVector;
				}

				///

				sf::Vector2f vec01 = ccc->ComplexCollision[i].v1 - currentTransform->Location;
				sf::Vector2f vec02 = ccc->ComplexCollision[i].v2 - currentTransform->Location;
				sf::Vector2f vec03 = ccc->ComplexCollision[i].v3 - currentTransform->Location;

				float _cos12 = vec01->*Cos(vec02);
				float _cos13 = vec01->*Cos(vec03);
				float _cos23 = vec02->*Cos(vec03);

				if (abs((acos(_cos12) + acos(_cos13) + acos(_cos23) - 2 * PI)) < 0.0001) {
					std::cout << "--------------" << std::endl;
					/*std::cout << "h_13: " << h_13 << std::endl;
					std::cout << "h_23: " << h_23 << std::endl;
					std::cout << "h_12: " << h_12 << std::endl;
					std::cout << "min_h: " << min_h << std::endl;*/

					//sf::Vector2f _normalVector = _camera_location - currentTransform->Location;
					float z_coord = -min_line.x * min_dist_to_center.y + min_line.y * min_dist_to_center.x;
					sf::Vector2f _normalVector = {
						min_line.y * z_coord,
						-min_line.x * z_coord
					};
					_normalVector = _normalVector->*Normalize();

					//currentTransform->Location += _normalVector * (min_h + RADIUS + 0.001f);
					currentTransform->Location += _normalVector * 0.001f;

					if (abs((acos(_cos12) + acos(_cos13) + acos(_cos23) - 2 * PI)) < 0.0001) {
						currentTransform->Location = { 0,0 };
					}
					//currentTransform->Location = currentDrop->OldLocation;

					//std::cout << "\n\n\n" << std::endl;
					//_entities->DestroyEntity(*item.Entity);
					//currentTransform->Location = _oldLocation;
					//system("pause");
				}
				//// Erema

				/*

				sf::Vector2f new_velocity = speed_comp->Speed - n * 2.f * n->*Dot(speed_comp->Speed);

				speed_comp->Speed = new_velocity * 1.f;

				currentTransform->Location = currentTransform->Location + n * (RADIUS - min_h);/**/
				//std::cout << "New location x: " << currentTransform->Location.x << " New location y: " << currentTransform->Location.y << std::endl;
				//system("pause");
				
			}
		}
		currentDrop->OldLocationCounter++;
		if (currentDrop->OldLocationCounter == 20) {
			currentDrop->OldLocation = currentTransform->Location;
			currentDrop->OldLocationCounter = 0;
		}
		

		// hardcode mood begin
	/*
		sf::Vector2f _normalVector = { 0, 0 };
		std::cout << "X: " << currentTransform->Location.x << "\tY: " << currentTransform->Location.y << std::endl;
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
			//currentSpeed->Speed.y = 0;
			currentTransform->Location = _oldLocation;

			_normalVector *= currentSpeed->Speed->*Length();
			_normalVector *= _normalVector->*Cos(currentSpeed->Speed);
			currentSpeed->Speed = { 0, 0 };
			currentSpeed->Speed += _normalVector;
		}	*/
		if ((currentTransform->Location - _oldLocation)->*Length() < (currentSpeed->Speed * _gameTime.FixedDeltaTime())->*Length() - 0.00001f) {
			currentSpeed->Speed -= (_gravitation * _gameTime.FixedDeltaTime()) * 1.5f;  // change
		}

		// hardcode mood end

		//std::cout << "x : " << currentTransform->Location.x << "\ty : " << currentTransform->Location.y << std::endl;
	}
	//std::cout << std::endl;
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