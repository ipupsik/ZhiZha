#pragma once

#include <bitset>

#include "TypeFamily.h"

struct SystemBase {
	friend struct UpdateSystem;
	friend struct FixedUpdateSystem;
	friend struct PostInitSystem;
	friend struct PostUpdateSystem;
	
	virtual ~SystemBase() = default;
};

struct UpdateSystem : virtual SystemBase {
	virtual void OnUpdate() = 0;
};

struct PostInitSystem : virtual SystemBase {
	virtual void OnPostInit() = 0;
};

struct FixedUpdateSystem : virtual SystemBase {
	virtual void OnFixedUpdate() = 0;
};

struct PostUpdateSystem : virtual SystemBase {
	virtual void OnPostUpdate() = 0;
};

template <typename T>
struct System : public virtual SystemBase {
	static std::size_t Type;
};

template <typename T>
std::size_t System<T>::Type = TypeFamily<SystemBase>::Type<T>();
