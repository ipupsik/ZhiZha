#include <functional>
#include <SFML/Graphics/Rect.hpp>
#include "Component.h"

struct ButtonComponent : public ComponentData<ButtonComponent> {
	sf::IntRect Bounds;
	std::function<void()> OnClick;
	std::function<void()> OnHover;
	std::function<void()> OnHoverEnds;
};