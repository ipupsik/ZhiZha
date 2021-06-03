#pragma once

#include "Component.h"

struct NameComponent: public ComponentData<NameComponent> {
	std::string Name;
};