#pragma once

#include "EntityManager.h"
#include "Scene.h"
#include <bitset>

class System {
	friend class SystemManager;

	bool _isActive = true;
	std::bitset<static_cast<int>(Scene::Count)> _workingScenes;

protected:
	EntityManager* _entities = nullptr;
	System() {
		_workingScenes.set(static_cast<int>(Scene::Main));
	}
	virtual ~System() = default;

public:
	[[nodiscard]] auto& GetWorkingScenes() const { return _workingScenes; }
	void SetActive(bool active = true) { _isActive = active; }
	[[nodiscard]] bool IsActive() const { return _isActive; }
	void BindToScene(Scene scene) { _workingScenes.set(static_cast<int>(scene)); }
	void UnbindFromScene(Scene scene) { _workingScenes.set(static_cast<int>(scene), false); }
};

/**
 * Система, которая вызывается каждое начало кадра.
 */
struct UpdateSystem : virtual System {
	virtual void OnUpdate() = 0;
};

/**
 * Система, которая делает что-то один раз при запуске программы.
 *
 * Note: нельзя вызывать ресурсозатратные методы
 */
struct PostInitSystem : virtual System {
	virtual void OnPostInit() = 0;
};

/**
 * Система, которая вызывается каждую 1/60 сек (независимо от других систем).
 *
 * Note: В этой системе нельзя использовать OpenGL
 */
struct FixedUpdateSystem : virtual System {
	virtual void OnFixedUpdate() = 0;
};

/**
 * Система, которая вызывается после отрисовки кадра
 */
struct PostUpdateSystem : virtual System {
	virtual void OnPostUpdate() = 0;
};

/**
 * Система, которая вызывается перед первым кадром
 */
struct InitSystem : virtual System {
	virtual void OnInit() = 0;
};

struct UnloadSystem: virtual System {
	virtual void OnSceneUnload(Scene scene) = 0;
};