#include "StaticMesh.h"

#include <string>
#include <iostream>
#include <fstream>
#include <glad/glad.h>

using namespace std;

void StaticMesh::Init()
{
	glGenBuffers(1, &IndexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, IndexVBO);
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * vertices.size(), vertices.begin()._Ptr, GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &IndexEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexEBO);
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face) * faces.size(), faces.begin()._Ptr, GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void StaticMesh::Draw()
{ 
	glBindBuffer(GL_ARRAY_BUFFER, IndexVBO);
	{
		glVertexPointer(3, GL_DOUBLE, 0, NULL);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexEBO);
	{
		glDrawElements(GL_TRIANGLES, 3 * faces.size(), GL_UNSIGNED_INT, NULL);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void StaticMesh::ReadFile(const char* filename)
{
	string s;
	ifstream fin(filename);
	if (!fin)
		return;
	while (fin >> s)
	{
		if (s == "v")
		{
			vertex v;
			fin >> v.x >> v.y >> v.z;
			vertices.push_back(v);
		}
		else if (s == "f")
		{
			char symbol;
			face f, n, uv;

			fin >> f.v1;
			fin >> symbol;
			fin >> uv.v1;
			fin >> symbol;
			fin >> n.v1;

			fin >> f.v2;
			fin >> symbol;
			fin >> uv.v2;
			fin >> symbol;
			fin >> n.v2;

			fin >> f.v3;
			fin >> symbol;
			fin >> uv.v3;
			fin >> symbol;
			fin >> n.v3;

			f.v1--;
			f.v2--;
			f.v3--;

			faces.push_back(f);
			faces_normal.push_back(n);
			faces_tex_coord.push_back(uv);
		}
		else if (s == "vn")
		{
			vertex vn;
			fin >> vn.x >> vn.y >> vn.z;
			normals.push_back(vn);
		}
		else if (s == "vt")
		{
			uv_vertex vt;
			fin >> vt.u >> vt.v;
			uvs.push_back(vt);
		}
	}
	std::cout << s;
}