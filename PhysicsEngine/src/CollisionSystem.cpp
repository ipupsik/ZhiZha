#include "System.h"
#include "Components/TransformComponent.h"
#include "GameTime.h"
#include "../PhysicsEngine/include/ComponentDrop.h"
#include "Components/CircleCollisionComponent.h"
#include "utils.h"

#include "Systems/CollisionSystem.h"

using namespace sf::Extensions::Vector2;

void CollisionSystem::OnFixedUpdate() {
	//нашли соседей шариков -- start
	const auto& items = _entities->GetEntitiesBy<CircleCollisionComponent, ComponentDrop>();

	for (auto& [components, current_entity] : items)
	{
		auto& [collision_current, drop_current] = components;

		for (auto& [components, other_entity] : items)
		{
			auto& [collision_other, drop_other] = components;

			if (collision_current == collision_other)
			{
				continue;
			}

			if (collision_current->Position->*Magnitude(collision_other->Position) <= 2 * collision_current->Radius)
			{
				drop_current->neighbours.push_back(other_entity);
			}

		}
	}
	//нашли соседей шариков -- end

	//находим векторы соседи_импакт -- start
	for (auto& [components, current_entity] : items)
	{
		auto& [collision_current, drop_current] = components;

		drop_current->Neighbour_impact = { 0, 0 };

		for (int i = 0; i < drop_current->neighbours.size(); ++i)
		{
			drop_current->Neighbour_impact += -_entities->GetComponent<CircleCollisionComponent>(*(drop_current->neighbours[i]))->Position + collision_current->Position;
		}
	}
	//находим векторы соседи_импакт -- end
}