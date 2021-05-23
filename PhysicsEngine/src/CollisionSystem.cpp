#include "System.h"
#include "Components/TransformComponent.h"
#include "GameTime.h"
#include "../PhysicsEngine/include/ComponentDrop.h"
#include "Components/CircleCollisionComponent.h"
#include "utils.h"
#include "../PhysicsEngine/include/DefinesPhysics.h"

#include "Systems/CollisionSystem.h"

using namespace sf::Extensions::Vector2;

void CollisionSystem::OnFixedUpdate() {
	//нашли соседей шариков -- start
	const auto& items = _entities->GetEntitiesBy<ComponentDrop>();

	for (auto& [components, current_entity] : items)
	{
		auto& [drop_current] = components;
		for (auto& [components, other_entity] : items)
		{
			auto& [drop_other] = components;
			if (drop_current->Position == drop_other->Position)
			{
				continue;
			}

			if (drop_current->Position->*Magnitude(drop_other->Position) <= 2 * RADIUS)
			{
				drop_current->neighbours.push_back(other_entity);
			}

		}
	}
	//нашли соседей шариков -- end

	//находим векторы соседи_импакт -- start
	for (auto& [components, current_entity] : items)
	{
		auto& [drop_current] = components;

		drop_current->Neighbour_impact = { 0, 0 };

		for (int i = 0; i < drop_current->neighbours.size(); ++i)
		{
			drop_current->Neighbour_impact += -_entities->GetComponent<ComponentDrop>(*(drop_current->neighbours[i]))->Position + drop_current->Position;
		}
	}
	//находим векторы соседи_импакт -- end
}