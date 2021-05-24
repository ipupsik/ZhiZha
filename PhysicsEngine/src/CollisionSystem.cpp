#include <Components/TransformComponent.h>
#include <iostream>
#include "ComponentDrop.h"
#include "utils.h"
#include "DefinesPhysics.h"

#include "Systems/CollisionSystem.h"

using namespace sf::Extensions::Vector2;

void CollisionSystem::OnFixedUpdate() {
	//����� ������� ������� -- start
	const auto& items = _entities->GetEntitiesBy<ComponentDrop, TransformComponent>();

	for (auto&[components, current_entity] : items) {
		auto&[drop_current, transformCurrent] = components;
		for (auto&[components, other_entity] : items) {
			auto&[drop_other, transformOther] = components;
			if (transformCurrent->Location == transformOther->Location) {
				continue;
			}

			// here use squared distance, because to get square is much easier, then to get square
			if (transformCurrent->Location->*SqrMagnitude(transformOther->Location)
					<= 4 * RADIUS * RADIUS) {
				drop_current->neighbours.push_back(other_entity);
			}
		}
	}
	//����� ������� ������� -- end

	//������� ������� ������_������ -- start
	for (auto&[components, current_entity] : items) {
		auto&[drop, transform] = components;

		drop->Neighbour_impact = { 0, 0 };

		for (int i = 0; i < drop->neighbours.size(); ++i) {
			drop->Neighbour_impact +=
					_entities->GetComponent<TransformComponent>(*(drop->neighbours[i]))->Location
							- transform->Location;
		}
	}
	//������� ������� ������_������ -- end
}