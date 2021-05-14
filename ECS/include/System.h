#pragma once

#include "EntityManager.h"
#include "TypeFamily.h"

struct SystemBase {
    // TODO remove friend statements
	friend struct UpdateSystem;
	friend struct FixedUpdateSystem;
	friend struct PostInitSystem;
	friend struct PostUpdateSystem;
	
	virtual ~SystemBase() = default;

protected:
	EntityManager& _entities = EntityManager::Current;
};

/**
 * Система, которая вызывается каждое начало кадра.
 */
struct UpdateSystem : virtual SystemBase {
	virtual void OnUpdate() = 0;
};

/**
 * Система, которая делает что-то один раз при запуске программы.
 *
 * Note: нельзя вызывать ресурсозатратные методы
 */
struct PostInitSystem : virtual SystemBase {
	virtual void OnPostInit() = 0;
};

/**
 * Система, которая вызывается каждую 1/60 сек (независимо от других систем).
 *
 * Note: В этой системе нельзя использовать OpenGL
 */
struct FixedUpdateSystem : virtual SystemBase {
	virtual void OnFixedUpdate() = 0;
};

/**
 * Система, которая вызывается после отрисовки кадра
 */
struct PostUpdateSystem : virtual SystemBase {
	virtual void OnPostUpdate() = 0;
};

// TODO delete
template <typename T>
struct System : public virtual SystemBase {
	static std::size_t Type;
};

template <typename T>
std::size_t System<T>::Type = TypeFamily<SystemBase>::Type<T>();
