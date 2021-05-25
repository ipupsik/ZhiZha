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
				}
			}

			auto& current_drop_comp = *(_entities->GetComponent<ComponentDrop>(*current_drop));
			current_drop_comp.is_moved = true;

			for (int j = 0; j < current_drop_comp.neighbours.size(); ++j)
			{
				auto& other_drop_comp = *(_entities->GetComponent<ComponentDrop>(*(current_drop_comp.neighbours[j])));
				if (!(other_drop_comp.is_moved) && !(other_drop_comp.is_in_queue))
				{
					other_drop_comp.is_in_queue = true;
					current_volume_comp->Perimetr_drops.push(current_drop_comp.neighbours[j]);
				}
			}

			current_drop_comp.is_in_queue = false;
			current_volume_comp->Perimetr_drops.pop();
		}
	}
}