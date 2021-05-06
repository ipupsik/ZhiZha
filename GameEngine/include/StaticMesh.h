#pragma once

#include <vector>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

class StaticMesh {
public:
	struct face {
		unsigned int v1, v2, v3;
	};

	// raw data
	std::vector<sf::Vector2f> vertices;
	std::vector<sf::Vector2f> normals;
	std::vector<sf::Vector2f> uvs;

	// elements data
	std::vector<face> faces;
	std::vector<face> faces_normal;
	std::vector<face> faces_tex_coord;

	unsigned int IndexEBO, IndexVBO;

public:
	void ReadFile(const sf::String& filename);
	void Init();
	void Draw();
};
