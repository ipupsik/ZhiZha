#pragma once

#include <SFML/System/Vector2.hpp>
#include <string>
#include <memory>

#include "TypeFamily.h"

class Component {
public:
	virtual ~Component() = default;
	virtual std::shared_ptr<Component> Copy() = 0;

	void operator delete(void*) = delete;
	void operator delete[](void*) = delete;
};

template <typename T>
struct ComponentData : public Component {
	static std::size_t Type;
};

template <typename T>
std::size_t ComponentData<T>::Type = TypeFamily<Component>::Type<T>();

struct TransformComponent : public ComponentData<TransformComponent> {
	sf::Vector2f Location, Rotation, Scale;

	TransformComponent(sf::Vector2f location, sf::Vector2f rotation, sf::Vector2f scale);

	std::shared_ptr<Component> Copy() override;
};
