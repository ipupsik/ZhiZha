#include "SystemManager.h"

SystemManager SystemManager::Current = SystemManager();

void SystemManager::PostInit() const {
	for (const auto& system : _postInits)
		system->OnPostInit();
}

void SystemManager::Update() const {
	for (const auto& system: _updates)
		system->OnUpdate();
}

void SystemManager::FixedUpdate() const {
	for (const auto& system: _fixedUpdates)
		system->OnFixedUpdate();
}

void SystemManager::PostUpdate() const {
	for (const auto& system: _postUpdates)
		system->OnPostUpdate();
}

void SystemManager::Init() const {
	for (const auto& system: _inits)
		system->OnInit();
}
