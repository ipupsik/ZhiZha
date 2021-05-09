#pragma once

#include <memory>

#include "Entity.h"
#include "TypeFamily.h"

struct Component {
	using Id = std::size_t;

	Entity::Id EntityId;

	virtual ~Component() = default;
	[[nodiscard]] virtual Component* Copy() const = 0;
};

template <typename T>
struct ComponentData : public Component {
	static Id Type;

	Component* Copy() const final {
		return new T(static_cast<T const&>(*this));
	}

protected:
	ComponentData() = default;
	ComponentData(const ComponentData&) = default;
	ComponentData(ComponentData&&) = default;
};

template <typename T>
std::size_t ComponentData<T>::Type = TypeFamily<Component>::Type<T>();
