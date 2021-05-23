#include "System.h"
#include "Components/TransformComponent.h"
#include "../PhysicsEngine/include/ComponentDrop.h"
#include "../PhysicsEngine/include/DefinesPhysics.h"
#include "utils.h"

#include "../PhysicsEngine/include/Systems/GravitationSystem.h"

using namespace sf::Extensions::Vector2;

void GravitationSystem::OnFixedUpdate() {
	// ниже вектор гравитации, который нужно будет отсюта срочно убрать, им производится все управление
	sf::Vector2f Gravitation = { 0, G };

	const auto& items = _entities->GetEntitiesBy<ComponentDrop>();

	for (auto& [components, entity] : items)
	{
		auto& [drop] = components;
		drop->Velocity += Gravitation * _gameTime.FixedDeltaTime();
	}
}