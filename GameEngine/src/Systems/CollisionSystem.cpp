#include "System.h"
#include "Components/TransformComponent.h"
#include "GameTime.h"
#include "Components/CircleCollisionComponent.h"
#include "utils.h"

#include "Systems/CollisionSystem.h"

using namespace sf::Extensions::Vector2;

//�������!!!!!

void CollisionSystem::OnFixedUpdate() {
	const auto& items = _entities->GetEntitiesBy<CircleCollisionComponent>();

	for (auto& [components, entity] : items)
	{
		auto& [collision_1] = components;

		for (auto& [components, current_entity] : items)
		{
			auto& [collision_2] = components;

			if (collision_1 == collision_2)
			{
				continue;
			}

			if (collision_1->Position->*Magnitude(collision_2->Position) <= 2 * collision_1->Radius)
			{
//				_entities->GetComponent<>(current_entity)
			}

		}
	}
}