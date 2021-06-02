#pragma once
#include "Component.h"

enum Layers { Game, Gui, Menu };

struct LayerComponent : public ComponentData<LayerComponent> {
	Layers Index;
};