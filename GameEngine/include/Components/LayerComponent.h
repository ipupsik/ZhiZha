#pragma once
#include "Component.h"

enum Layers { Background, Game, Gui };

struct LayerComponent : public ComponentData<LayerComponent> {
	Layers Index;
};