#include "SystemManager.h"

SystemManager::~SystemManager() {
	for (auto item : _updates)
		delete item;
	for (auto item : _fixedUpdates)
		delete item;
	for (auto item : _inits)
		delete item;
	for (auto item : _postInits)
		delete item;
	for (auto item : _postUpdates)
		delete item;
}

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
