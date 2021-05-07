#pragma once

#include "TypeFamily.h"

struct SystemBase {
	virtual ~SystemBase() = default;
};

struct UpdateSystem: SystemBase {
	virtual void OnUpdate() = 0;
};

struct PostInitSystem: SystemBase {
	virtual void OnPostInit() = 0;
};

struct FixedUpdateSystem: SystemBase {
	virtual void OnFixedUpdate() = 0;
};

struct PostUpdateSystem: SystemBase {
	virtual void OnPostUpdate() = 0;
};

template <typename T>
struct System: public SystemBase {
	static std::size_t Type;
};

template <typename T>
std::size_t System<T>::Type = TypeFamily<SystemBase>::Type<T>();
