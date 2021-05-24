#pragma once

#include <string>
#include <utility>
#include <vector>
#include "glad/glad.h"

#include "ResourceFile.h"
#include "SFML/Graphics.hpp"

class MeshResource : public ResourceFile {
public:
	std::vector<sf::Vector2f> _vertices;
	std::vector<sf::Vector2f> _normals;
	std::vector<sf::Vector2f> _uvs;
	std::vector<sf::Vector2f> _uvsInit;

	std::vector<sf::Vector3<unsigned int>> _faces;
	std::vector<sf::Vector3<unsigned int>> _facesNormal;
	std::vector<sf::Vector3<unsigned int>> _facesTexCoord;

public:

	GLuint _indexEBO = 0, _indexVBO = 0, _indexTexVBO = 0, _indexVAO = 0;

	void initMesh();
	void readFile();
	explicit MeshResource(std::string&& filename);
};