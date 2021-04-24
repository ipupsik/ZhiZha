#pragma once

#include <vector>

#include "PupsyaTypes.h"

class StaticMesh
{
public:
	struct face {
		unsigned int v1, v2, v3;
	};
	// raw data
	std::vector<Vec2D> vertices;
	std::vector<Vec2D> normals;
	std::vector<Vec2D> uvs;

	// elements data
	std::vector<face> faces;
	std::vector<face> faces_normal;
	std::vector<face> faces_tex_coord;

	unsigned int IndexEBO, IndexVBO;

public:
	void ReadFile(const char* filename);
	void Init();
	void Draw();
};