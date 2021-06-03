#include <DefinesPhysics.h>
#include "ComponentDrop.h"

#include "Systems/GravitationSystem.h"
#include "Components/SpeedComponent.h"

void GravitationSystem::OnFixedUpdate() {
	// ���� ������ ����������, ������� ����� ����� ������ ������ ������, �� ������������ ��� ����������

	const auto& items = _entities->GetEntitiesBy<SpeedComponent>();

	for (auto&[components, entity] : items) {
		auto&[speed] = components;
		speed->Speed += _gravitation * _gameTime.FixedDeltaTime();
	}
}

void GravitationSystem::OnSceneUnload(Scene scene) {
	_gravitation = sf::Vector2f{0, G / 20};
}
