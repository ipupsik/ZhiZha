#pragma once

#include <string>
#include <utility>
#include <vector>
#include "glad/glad.h"

#include "ResourceFile.h"
#include "SFML/Graphics.hpp"
#include "ObjectDrawable.h"

class MeshResource : public ResourceFile {
private:
	void readFile();

	std::vector<sf::Vector2f> _vertices;
	std::vector<sf::Vector2f> _normals;
	std::vector<sf::Vector2f> _uvs;
	std::vector<sf::Vector2f> _uvsInit;

	std::vector<sf::Vector3<unsigned int>> _faces;
	std::vector<sf::Vector3<unsigned int>> _facesNormal;
	std::vector<sf::Vector3<unsigned int>> _facesTexCoord;

	ObjectDrawable _obj;
public:
	ObjectDrawable& Object() { return _obj; }

	explicit MeshResource(std::string&& filename);
};