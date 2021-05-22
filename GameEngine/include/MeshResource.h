#pragma once

#include <string>
#include <vector>
#include "glad/glad.h"

#include "ResourceFile.h"
#include "SFML/Graphics.hpp"

class MeshResource : public ResourceFile {
private:
	void readFile(std::string&& filename);
	void initMesh();

	std::vector<sf::Vector2f> _vertices;
	std::vector<sf::Vector2f> _normals;
	std::vector<sf::Vector2f> _uvs;
	std::vector<sf::Vector2f> _uvsInit;

	std::vector<sf::Vector3<unsigned int>> _faces;
	std::vector<sf::Vector3<unsigned int>> _facesNormal;
	std::vector<sf::Vector3<unsigned int>> _facesTexCoord;

	GLuint _ebo;
	sf::VertexBuffer _vbo;

public:
	[[nodiscard]] auto EBO() const { return _ebo; }
	[[nodiscard]] auto& VBO() const { return _vbo; }
	[[nodiscard]] auto Faces() const { return _faces.size(); }

	explicit MeshResource(std::string&& filename);
};
