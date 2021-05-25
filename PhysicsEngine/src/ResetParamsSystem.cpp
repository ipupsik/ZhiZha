#include "ComponentDrop.h"
#include "ComponentVolume.h"

#include "Systems/ResetParamsSystem.h"

#include "Components/TransformComponent.h"

void ResetParamsSystem::OnFixedUpdate()
{
	const auto& drops = _entities->GetEntitiesBy<ComponentDrop, TransformComponent>();

	for (auto& [components, cur_entity] : drops)
	{
		auto&[drop_comp, transform] = components;

		if (transform->Location.y > 1200)
			_entities->DestroyEntity(*cur_entity);

		drop_comp->neighbours.resize(0);

		drop_comp->is_force_calculated = false;
		drop_comp->is_in_queue = false;
		drop_comp->is_in_volume = false;
		drop_comp->is_volume_calculated = false;
		drop_comp->is_moved = false;
	}

	const auto& volumes = _entities->GetEntitiesBy<ComponentVolume>();

	for (auto& [components, cur_entity] : volumes)
	{
		_entities->DestroyEntity(*cur_entity);
	}
}
