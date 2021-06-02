#pragma once

#include <glad/glad.h>
#include "SFML/Graphics.hpp"
#include "ResourceFile.h"

class TextureResource : public ResourceFile
{
public:
	GLuint TextureId;
	sf::Texture Texture;

	explicit TextureResource(std::string&& filename);
};