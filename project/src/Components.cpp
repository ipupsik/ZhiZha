#include "Components.h"

#include <memory>

Component* TestComponent::Copy() {
	return new TestComponent(*this);
}

Component* NameComponent::Copy() {
	return new NameComponent(*this);
}

Component* TransformComponent::Copy() {
	return new TransformComponent(*this);
}
