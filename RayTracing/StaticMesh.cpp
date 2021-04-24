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
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2D) * vertices.size(), vertices.begin()._Ptr, GL_STATIC_DRAW);
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
		glVertexPointer(2, GL_FLOAT, 0, NULL);
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
			Vec2D v;
			fin >> v.X >> v.Y;

			float tmp;
			fin >> tmp;

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
			Vec2D vn;
			fin >> vn.X >> vn.Y;

			float tmp;
			fin >> tmp;

			normals.push_back(vn);
		}
		else if (s == "vt")
		{
			Vec2D vt;
			fin >> vt.X >> vt.Y;
			uvs.push_back(vt);
		}
		else
		{
			string tmp;
			getline(fin, tmp);
		}
	}
	std::cout << s;
}