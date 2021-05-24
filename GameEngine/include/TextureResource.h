#pragma once

#include <glad/glad.h>
#include "SFML/Graphics.hpp"
#include "ResourceFile.h"

class TextureResource : public ResourceFile {
	sf::Texture _texture;
public:
	auto* GetTexture() { return &_texture; }

	explicit TextureResource(std::string&& filename);
};