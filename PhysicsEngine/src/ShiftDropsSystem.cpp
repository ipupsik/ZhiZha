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

				if (abs((acos(_cos12) + acos(_cos13) + acos(_cos23) - 2 * PI)) < 0.1) {
					float z_coord = -min_line.x * min_dist_to_center.y + min_line.y * min_dist_to_center.x;

					sf::Vector2f _normalVector = {
						min_line.y * z_coord,
						-min_line.x * z_coord
					};

					currentSpeed->Speed = _normalVector * 0.5f;
					currentTransform->Location = _oldLocation + _normalVector * 0.1f;
				}
			}
		}
		/*currentDrop->OldLocationCounter++;
		if (currentDrop->OldLocationCounter == 20) {
			currentDrop->OldLocation = currentTransform->Location;
			currentDrop->OldLocationCounter = 0;
		}*/

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