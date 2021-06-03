#include "ComponentDrop.h"

#include "Systems/GravitationSystem.h"
#include "Components/SpeedComponent.h"

void GravitationSystem::OnFixedUpdate() {
	// ���� ������ ����������, ������� ����� ����� ������ ������ ������, �� ������������ ��� ����������

	const auto& items = _entities->GetEntitiesBy<SpeedComponent>();

	for (auto&[components, entity] : items) {
		auto&[speed] = components;
		speed->Speed += _gravitation * _gameTime.FixedDeltaTime() / 2.f;
	}
}