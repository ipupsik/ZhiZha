#pragma once

#include "ResourceFile.h"
#include "SFML/Graphics.hpp"

class FontResource: public ResourceFile {
	sf::Font _font;
public:
	explicit FontResource(const std::string& name): ResourceFile(name + ".ttf") {
		_font.loadFromStream(*this);
	}

	auto& Font() { return _font; }
};