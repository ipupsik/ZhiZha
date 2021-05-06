#pragma once

#include <SFML/System/Vector2.hpp>
#include <string>
#include <memory>

class Component {
public:
	virtual size_t Type() = 0;
	virtual std::shared_ptr<Component> Copy() = 0;
};

struct TransformComponent : public Component {
	sf::Vector2f Location, Rotation, Scale;

	TransformComponent(sf::Vector2f location, sf::Vector2f rotation, sf::Vector2f scale);

	size_t Type() override;
	std::shared_ptr<Component> Copy() override;
};

struct TestComponent : public Component {
	int Data;

	explicit TestComponent(int data);

	size_t Type() override;
	std::shared_ptr<Component> Copy() override;
};

struct NameComponent : public Component {
	std::string Name;

	explicit NameComponent(std::string name);

	size_t Type() override;
	std::shared_ptr<Component> Copy() override;
};
