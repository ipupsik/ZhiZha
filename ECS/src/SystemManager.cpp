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

template <std::derived_from<System> T, typename ...Args>
constexpr auto doIfActive(void (T::*tick)(Args...), Args... args) {
	return [=](T* system) {
		if (system->IsActive())
			(system->*tick)(args...);
	};
}

void SystemManager::PostInit() const {
	doFor(_postInits, doIfActive(&PostInitSystem::OnPostInit));
}

void SystemManager::Update() const {
	doFor(_updates, doIfActive(&UpdateSystem::OnUpdate));
}

void SystemManager::FixedUpdate() const {
	doFor(_fixedUpdates, doIfActive(&FixedUpdateSystem::OnFixedUpdate));
}

void SystemManager::PostUpdate() const {
	doFor(_postUpdates, doIfActive(&PostUpdateSystem::OnPostUpdate));
}

void SystemManager::Init() const {
	doFor(_inits, doIfActive(&InitSystem::OnInit));
}

constexpr auto updateActivity(Scene scene) {
	return [scene](System* system) {
		if (system->GetWorkingScenes()[static_cast<int>(scene)])
			system->SetActive(true);
		else
			system->SetActive(false);
	};
}

void SystemManager::ActivateInitSystems(Scene scene) {
	doFor(_postInits, updateActivity(scene));
	doFor(_inits, updateActivity(scene));
}

void SystemManager::ActivateOtherSystems(Scene scene) {
	doFor(_updates, updateActivity(scene));
	doFor(_fixedUpdates, updateActivity(scene));
	doFor(_postUpdates, updateActivity(scene));
	doFor(_unloads, updateActivity(scene));
}

void SystemManager::UnloadScene(Scene scene) const {
	doFor(_unloads, doIfActive(&UnloadSystem::OnSceneUnload, scene));
}
