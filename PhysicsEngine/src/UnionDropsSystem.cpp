
#include "System.h"
#include "Components/TransformComponent.h"
#include "GameTime.h"
#include "../PhysicsEngine/include/ComponentDrop.h"
#include "../PhysicsEngine/include/ComponentVolume.h"
#include "../PhysicsEngine/include/DefinesPhysics.h"
#include "utils.h"

#include "Systems/CollisionSystem.h"
#include "../PhysicsEngine/include/Systems/UnionDropsSystem.h"

using namespace sf::Extensions::Vector2;

void UnionDropsSystem::OnFixedUpdate()
{
	const auto& items = _entities->GetEntitiesBy<ComponentDrop>();
	Entity& Volume = _entities->CreateEntity();

	auto& volume_component = _entities->GetOrAddComponent<ComponentVolume>(Volume);

	for (auto& [components, drop] : items) {
		auto& [drop_components] = components;
		if (!(drop_components->is_in_volume)) {
			auto& copy = _entities->Instantiate(Volume);
			CheckAndAddDrop(*(_entities->GetComponent<ComponentVolume>(copy)), *drop_components, *drop);
		}
	}
}

void UnionDropsSystem::AddToVolume(auto& volume_component, Entity& drop)
{
	volume_component.Perimetr_drops.push(&drop);
}

void UnionDropsSystem::CheckAndAddDrop(ComponentVolume& volume_component, ComponentDrop& component_drop, Entity& drop)
{
	if (!(component_drop.is_in_volume)) {

		if (component_drop.neighbours.size() < 3) {
			AddToVolume(volume_component, drop);
		}

		if (component_drop.neighbours.size() == 3) {
			if (component_drop.Neighbour_impact->*Length() >= RADIUS) {
				AddToVolume(volume_component, drop);
			}
		}
		component_drop.Neighbour_impact->*Normalize();
		component_drop.is_in_volume = true;

		for (auto& neighbour : component_drop.neighbours) {
			CheckAndAddDrop(volume_component,*(_entities->GetComponent<ComponentDrop>(*neighbour)), *neighbour);
		}
		// тут должна быть проверка на соседство со стенкой
	}
}
