#pragma once

#include <memory>

#include "Entity.h"
#include "TypeFamily.h"

struct Component {
	using Id = std::size_t;

	Entity::Id EntityId;

	virtual ~Component() = default;
	virtual Component* Copy() = 0;
};

template <typename T>
struct ComponentData : public Component {
	static Id Type;
};

template <typename T>
std::size_t ComponentData<T>::Type = TypeFamily<Component>::Type<T>();
