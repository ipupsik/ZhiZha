#pragma once

#include "Component.h"

struct TestComponent : public ComponentData<TestComponent> {
	int Data;

	explicit TestComponent(int data);

	std::shared_ptr<Component> Copy() override;
};

struct NameComponent : public ComponentData<NameComponent> {
	std::string Name;

	explicit NameComponent(std::string name);

	std::shared_ptr<Component> Copy() override;
};
