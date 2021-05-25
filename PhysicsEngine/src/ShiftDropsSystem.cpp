#include <Components/TransformComponent.h>

#include "ComponentDrop.h"
#include "ComponentVolume.h"
#include "Components/SpeedComponent.h"
#include "utils.h"
#include "DefinesPhysics.h"

#include "Systems/ShiftDropsSystem.h"

using namespace sf::Extensions::Vector2;

void ShiftDropsSystem::OnFixedUpdate()
{
	const auto& items = _entities->GetEntitiesBy<ComponentVolume>();

	for (auto& [current_components_volume, current_entity] : items)
	{
		auto&[current_volume_comp] = current_components_volume;
		for (int i = 0; i < current_volume_comp->Perimetr_drops.size(); ++i)
		{
			Entity* current_drop = current_volume_comp->Perimetr_drops.front();
			auto current_drop_transform = _entities->GetComponent<TransformComponent>(*current_drop);
			auto& current_drop_speed = *(_entities->GetComponent<SpeedComponent>(*current_drop));

			if (!current_drop_transform) continue;

			sf::Vector2f _oldLocation = current_drop_transform->Location;

			// here we need check collision with walls !!!!!!!!!!!!!!!!!!!

			// collision with other balls in volume (if we dont have collision with walls)

			current_drop_transform->Location += current_drop_speed.Speed;

			const auto& all_other_drops = _entities->GetEntitiesBy<ComponentDrop, TransformComponent>();

			for (auto& [current_components_drop, current_other_drop] : all_other_drops)
			{
				
				if (current_other_drop == current_drop)
				{
					continue;
				}

				auto& [other_drop_comp, other_transform_comp] = current_components_drop;

				if (current_drop_transform->Location->*SqrMagnitude(other_transform_comp->Location)
					<= 4 * RADIUS * RADIUS)
				{
					sf::Vector2f vector_centers = current_drop_transform->Location - other_transform_comp->Location;

					float shift_lenght = 2 * RADIUS - vector_centers->*Length();

					shift_lenght *= current_drop_speed.Speed->*Cos(-vector_centers);

					sf::Vector2f shift_vector = current_drop_speed.Speed->*Normalize();
					shift_vector.x *= shift_lenght;
					shift_vector.y *= shift_lenght;

					current_drop_transform->Location -= shift_vector;

					current_drop_speed.Speed = (current_drop_transform->Location - _oldLocation);
					current_drop_speed.Speed.x /= _gameTime.FixedDeltaTime() * 50;
					current_drop_speed.Speed.y /= _gameTime.FixedDeltaTime() * 50;
				}
			}

			/*if (true) {
				current_drop_speed.Speed = (current_drop_transform->Location - _oldLocation);/////////
				current_drop_speed.Speed.x /= _gameTime.FixedDeltaTime() * 50;
				current_drop_speed.Speed.y /= _gameTime.FixedDeltaTime() * 50;
			}*/

			auto& current_drop_comp = *(_entities->GetComponent<ComponentDrop>(*current_drop));
			current_drop_comp.is_moved = true;

			float _wallY = 500; // take from another file
			float _wallThickness = 2; // take from another file

			if (current_drop_transform->Location.y > _wallY - _wallThickness - 2 * RADIUS
				&& current_drop_transform->Location.x < 1000
				&& current_drop_transform->Location.x > 0) {
				current_drop_transform->Location.y = _wallY - _wallThickness - 2 * RADIUS;
				current_drop_speed.Speed.y = 0;
				current_volume_comp->Is_Interract_Wall = true;
			}

			for (auto neighbour : current_drop_comp.neighbours) {
				auto& other_drop_comp = *(_entities->GetComponent<ComponentDrop>(*neighbour));
				if (!(other_drop_comp.is_moved) && !(other_drop_comp.is_in_queue))
				{
					other_drop_comp.is_in_queue = true;
					current_volume_comp->Perimetr_drops.push(neighbour);
				}
			}

			current_drop_comp.is_in_queue = false;
			current_volume_comp->Perimetr_drops.pop();
		}
	}
}