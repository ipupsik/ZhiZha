#pragma once

#include "EntityManager.h"

class System {
	friend class SystemManager;
	
protected:
	EntityManager* _entities = nullptr;
	System() = default;
	virtual ~System() = default;
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
struct InitSystem: virtual System {
	virtual void OnInit() = 0;
};