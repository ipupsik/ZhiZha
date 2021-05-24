#include "System.h"
#include "Components/TransformComponent.h"
#include "Components/SpeedComponent.h"
#include "GameTime.h"
#include "../PhysicsEngine/include/ComponentVolume.h"
#include "../PhysicsEngine/include/ComponentDrop.h"
#include "utils.h"
#include "DefinesPhysics.h"

#include "Systems/ForceCalculationSystem.h"

using namespace sf::Extensions::Vector2;

void ForceCalculationSystem::OnFixedUpdate() {
	const auto& items = _entities->GetEntitiesBy<ComponentVolume>();

	for (auto& [components, volume] : items) {
		auto& [volum_components] = components;
		if ((volum_components->Is_Interract_Wall))
		{
			FindVolumPositions(*(volum_components->Perimetr_drops.back()), volum_components->Top_Position, volum_components->Bottom_Position_Interract_Wall);
		}
	}
}

void ForceCalculationSystem::FindVolumPositions(Entity& drop, sf::Vector2f& Top_Position, sf::Vector2f& Bottom_Position_Interract_Wall) {
	auto& component_drop = *(_entities->GetComponent<ComponentDrop>(drop));

	if (!component_drop.is_volume_calculated) {
		auto& component_transform = *(_entities->GetComponent<TransformComponent>(drop));
		auto& component_speed = *(_entities->GetComponent<SpeedComponent>(drop));

		if (component_transform.Location.x > Top_Position.x) {
			Top_Position.x = component_transform.Location.x;  // it isn't true
		}

		if (component_transform.Location.y > Top_Position.y) {
			Top_Position.y = component_transform.Location.y; // it isn't true
		}

		component_drop.is_volume_calculated = true;

		for (auto& neighbour : component_drop.neighbours) {
			FindVolumPositions(*neighbour, Top_Position, Bottom_Position_Interract_Wall);
		}
	}
}

void ForceCalculationSystem::ForceCalculation(Entity& drop, sf::Vector2f& Top_Position, sf::Vector2f& Bottom_Position_Interract_Wall) {
	auto& component_drop = *(_entities->GetComponent<ComponentDrop>(drop));

	if (!component_drop.is_force_calculated) {
		auto& component_transform = *(_entities->GetComponent<TransformComponent>(drop));
		auto& component_speed = *(_entities->GetComponent<SpeedComponent>(drop));

		sf::Vector2f _columnHeight = (Top_Position - component_transform.Location);
		sf::Vector2f _maxColumnHeight = (Top_Position - Bottom_Position_Interract_Wall);

		_columnHeight *= _columnHeight->*Cos(_gravitation);
		_maxColumnHeight *= _maxColumnHeight->*Cos(_gravitation);

		if (_columnHeight->*Length() <= _maxColumnHeight->*Length()) {
			component_drop.Neighbour_impact.x *= (_columnHeight->*Length() * DENSITY * G) - (component_drop.neighbours.size() * SURFACE_FORCE) * _gameTime.FixedDeltaTime() / MASS;
			component_drop.Neighbour_impact.y *= (_columnHeight->*Length() * DENSITY * G) - (component_drop.neighbours.size() * SURFACE_FORCE) * _gameTime.FixedDeltaTime() / MASS;

			component_speed.Speed = component_drop.Neighbour_impact;
		}

		component_drop.is_force_calculated = true;

		for (auto& neighbour : component_drop.neighbours) {
			FindVolumPositions(*neighbour, Top_Position, Bottom_Position_Interract_Wall);
		}
	}
}