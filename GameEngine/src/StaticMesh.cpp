#include "StaticMesh.h"

#include <string>
#include <iostream>
#include <fstream>

//FIXME glfw -> sfml

using namespace std;

void StaticMesh::Init() {
	//	glGenBuffers(1, &IndexVBO);
	//	glBindBuffer(GL_ARRAY_BUFFER, IndexVBO);
	//	{
	//		glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2D) * vertices.size(), &*vertices.begin(), GL_STATIC_DRAW);
	//	}
	//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//
	//	glGenBuffers(1, &IndexEBO);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexEBO);
	//	{
	//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face) * faces.size(), &*faces.begin(), GL_STATIC_DRAW);
	//	}
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void StaticMesh::Draw() {
	//	glBindBuffer(GL_ARRAY_BUFFER, IndexVBO);
	//	{
	//		glVertexPointer(2, GL_FLOAT, 0, NULL);
	//	}
	//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexEBO);
	//	{
	//		glDrawElements(GL_TRIANGLES, 3 * faces.size(), GL_UNSIGNED_INT, NULL);
	//	}
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void StaticMesh::ReadFile(const sf::String& filename) {
	string s;
	ifstream fin(filename.toAnsiString());
	if (!fin)
		return;
	while (fin >> s) {
		if (s == "v") {
			sf::Vector2f v;
			fin >> v.x >> v.y;

			float tmp;
			fin >> tmp;

			vertices.push_back(v);
		}
		else if (s == "f") {
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
		else if (s == "vn") {
			sf::Vector2f vn;
			fin >> vn.x >> vn.y;

			float tmp;
			fin >> tmp;

			normals.push_back(vn);
		}
		else if (s == "vt") {
			sf::Vector2f vt;
			fin >> vt.x >> vt.y;
			uvs.push_back(vt);
		}
		else {
			string tmp;
			getline(fin, tmp);
		}
	}
	std::cout << s;
}
