#include "ComponentDrop.h"
#include "ComponentVolume.h"
#include <iostream>

#include "Systems/ResetParamsSystem.h"

#include "Components/TransformComponent.h"

void ResetParamsSystem::OnFixedUpdate()
{
	const auto& drops = _entities->GetEntitiesBy<ComponentDrop, TransformComponent>();

	for (auto& [components, cur_entity] : drops)
	{
		auto&[drop_comp, transform] = components;

		drop_comp->neighbours.clear();

		drop_comp->is_force_calculated = false;
		drop_comp->is_in_queue = false;
		drop_comp->is_in_volume = false;
		drop_comp->is_volume_calculated = false;
		drop_comp->is_moved = false;
		drop_comp->if_changed_speed = false;
	}

	const auto& volumes = _entities->GetEntitiesBy<ComponentVolume>();

	for (auto& [components, cur_entity] : volumes)
	{
		_entities->DestroyEntity(*cur_entity);
	}
}
