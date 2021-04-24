#ifndef _H_OBJ3D_
#define _H_OBJ3D_

#include <vector>

class StaticMesh
{
	struct vertex {
		double x;
		double y;
		double z;
	};
	struct uv_vertex {
		double u;
		double v;
	};
	struct face {
		unsigned int v1, v2, v3;
	};
	// raw data
	std::vector<vertex> vertices;
	std::vector<vertex> normals;
	std::vector<uv_vertex> uvs;

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

#endif