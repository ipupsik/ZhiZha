#pragma once

#include "Entity.h"
#include "TypeFamily.h"

struct Component {
	using Id = std::size_t;

private:
	friend class EntityManager;
	Entity* _entity = nullptr;

public:
	[[nodiscard]] Entity& GetEntity() const { return *_entity; }
	virtual ~Component() = default;
	[[nodiscard]] virtual Component* Copy() const = 0;
};

template <typename T>
struct ComponentData : public Component {
	static Id Type;

	[[nodiscard]] Component* Copy() const final {
		return new T(static_cast<T const&>(*this));
	}

protected:
	ComponentData() = default;
	ComponentData(const ComponentData&) = default;
	ComponentData(ComponentData&&) noexcept = default;
};

template <typename ...Args>
struct ComplexComponent {
	std::tuple<Args*...> Components;
	Entity* Entity{};

	ComplexComponent() = default;
};

template <typename T>
std::size_t ComponentData<T>::Type = TypeFamily<Component>::Type<T>();
