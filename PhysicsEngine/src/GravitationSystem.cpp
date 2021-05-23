#include "ComponentDrop.h"

#include "Systems/GravitationSystem.h"

void GravitationSystem::OnFixedUpdate() {
	// ���� ������ ����������, ������� ����� ����� ������ ������ ������, �� ������������ ��� ����������

	const auto& items = _entities->GetEntitiesBy<ComponentDrop>();

	for (auto&[components, entity] : items) {
		auto&[drop] = components;
		drop->Velocity += _gravitation * _gameTime.FixedDeltaTime();
	}
}