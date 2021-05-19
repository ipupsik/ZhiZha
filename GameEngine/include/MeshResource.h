#pragma once

#include <string>
#include <vector>
#include "glad/glad.h"

#include "ResourceFile.h"
#include "SFML/System/Vector2.hpp"

class MeshResource : public ResourceFile {
public:
	struct Face {
		unsigned int v1, v2, v3;
	};
	
	std::vector<sf::Vector2f> _vertices;
	std::vector<sf::Vector2f> _normals;
	std::vector<sf::Vector2f> _uvs;
	std::vector<sf::Vector2f> _uvsInit;

	std::vector<Face> _faces;
	std::vector<Face > _facesNormal;
	std::vector<Face> _facesTexCoord;

	GLuint _indexEBO = 0, _indexVBO = 0, _indexTexVBO = 0, _indexVAO = 0;

	void initMesh();
	void readFile(std::string&& filename);
	explicit MeshResource(std::string&& filename);

	//void LoadContent() final;
};
