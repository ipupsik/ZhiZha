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
	tickIfActive(_postInits, &PostInitSystem::OnPostInit);
}

void SystemManager::Update() const {
	tickIfActive(_updates, &UpdateSystem::OnUpdate);
}

void SystemManager::FixedUpdate() const {
	tickIfActive(_fixedUpdates, &FixedUpdateSystem::OnFixedUpdate);
}

void SystemManager::PostUpdate() const {
	tickIfActive(_postUpdates, &PostUpdateSystem::OnPostUpdate);
}

void SystemManager::Init() const {
	tickIfActive(_inits, &InitSystem::OnInit);
}
