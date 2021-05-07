#include "Components.h"

#include <memory>
TestComponent::TestComponent(int data) : Data(data) {}

std::shared_ptr<Component> TestComponent::Copy() {
	return std::make_shared<TestComponent>(*this);
}

NameComponent::NameComponent(std::string name) : Name(std::move(name)) {}

std::shared_ptr<Component> NameComponent::Copy() {
	return std::make_shared<NameComponent>(*this);
}
