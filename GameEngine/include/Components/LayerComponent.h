#pragma once
#include "Component.h"

enum Layers { Game, Gui };

struct LayerComponent : public ComponentData<LayerComponent> {
	Layers Index;
};