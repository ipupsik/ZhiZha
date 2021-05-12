#include "SystemManager.h"

SystemManager SystemManager::Current = SystemManager();

void SystemManager::PostInit() const {
	const auto type = TypeFamily<SystemBase>::Type<PostInitSystem>();
	
	if (!_systemsTable.contains(type))
		return;

	for (const auto& system : _systemsTable.at(type))
		std::dynamic_pointer_cast<PostInitSystem>(system)->OnPostInit();
}

void SystemManager::Update() const {
	const auto type = TypeFamily<SystemBase>::Type<UpdateSystem>();

	if (!_systemsTable.contains(type))
		return;

	for (const auto& system : _systemsTable.at(type))
		std::dynamic_pointer_cast<UpdateSystem>(system)->OnUpdate();
}

void SystemManager::FixedUpdate() const {
	const auto type = TypeFamily<SystemBase>::Type<FixedUpdateSystem>();

	if (!_systemsTable.contains(type))
		return;

	for (const auto& system : _systemsTable.at(type))
		std::dynamic_pointer_cast<FixedUpdateSystem>(system)->OnFixedUpdate();
}

void SystemManager::PostUpdate() const {
	const auto type = TypeFamily<SystemBase>::Type<PostUpdateSystem>();

	if (!_systemsTable.contains(type))
		return;

	for (const auto& system : _systemsTable.at(type))
		std::dynamic_pointer_cast<PostUpdateSystem>(system)->OnPostUpdate();
}
