#include "MeshResource.h"

#include <iostream>
#include <fstream>

void MeshResource::readFile(std::string&& filename) {
	std::string s = filename;
	std::ifstream fin(s);
	if (!fin)
		return;
	while (fin >> s) {
		if (s == "v") {
			sf::Vector2f v;
			fin >> v.x >> v.y;

			float tmp;
			fin >> tmp;

			_vertices.push_back(v);
		}
		else if (s == "f") {
			char symbol;
			Face f{}, n{}, uv{};

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

			uv.v1--;
			uv.v2--;
			uv.v3--;

			_faces.push_back(f);
			_facesNormal.push_back(n);
			_facesTexCoord.push_back(uv);
		}
		else if (s == "vn") {
			sf::Vector2f vn;
			fin >> vn.x >> vn.y;

			float tmp;
			fin >> tmp;

			_normals.push_back(vn);
		}
		else if (s == "vt") {
			sf::Vector2f vt;
			fin >> vt.x >> vt.y;
			_uvsInit.emplace_back(1.0f - vt.x, vt.y);
		}
		else {
			std::string tmp;
			std::getline(fin, tmp);
		}
	}
	_uvs.resize(_uvsInit.size());
	for (auto i = 0; i < _faces.size(); i++) {
		_uvs[_faces[i].v1] = _uvsInit[_facesTexCoord[i].v1];
		_uvs[_faces[i].v2] = _uvsInit[_facesTexCoord[i].v2];
		_uvs[_faces[i].v3] = _uvsInit[_facesTexCoord[i].v3];
	}
}

void MeshResource::initMesh() {
	glGenBuffers(1, &_indexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _indexVBO);
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(sf::Vector2f) * _vertices.size(), &*_vertices.begin(), GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &_indexTexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _indexTexVBO);
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(sf::Vector2f) * _uvs.size(), &*_uvs.begin(), GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &_indexEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexEBO);
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Face) * _faces.size(), &*_faces.begin(), GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &_indexVAO);
	glBindVertexArray(_indexVAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, _indexVBO);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, _indexTexVBO);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 0, nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);
}

MeshResource::MeshResource(std::string&& filename) : ResourceFile(std::move(filename + ".obj")) {

	readFile(std::move(Name()));
	initMesh();
}
