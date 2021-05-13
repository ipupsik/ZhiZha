#include "MeshResource.h"

#include <iostream>

#include "ResourceFile.h"

void MeshResource::readFile(ResourceFile&& res) {
	std::string s;
	while (res >> s) {
		if (s == "v") {
			sf::Vector2f v;
			res >> v.x >> v.y;

			float tmp;
			res >> tmp;

			_vertices.push_back(v);
		}
		else if (s == "f") {
			char symbol;
			Face f{}, n{}, uv{};

			res >> f.v1;
			res >> symbol;
			res >> uv.v1;
			res >> symbol;
			res >> n.v1;

			res >> f.v2;
			res >> symbol;
			res >> uv.v2;
			res >> symbol;
			res >> n.v2;

			res >> f.v3;
			res >> symbol;
			res >> uv.v3;
			res >> symbol;
			res >> n.v3;

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
			res >> vn.x >> vn.y;

			float tmp;
			res >> tmp;

			_normals.push_back(vn);
		}
		else if (s == "vt") {
			sf::Vector2f vt;
			res >> vt.x >> vt.y;
			_uvsInit.emplace_back(1.0f - vt.x, vt.y);
		}
		else {
			std::string tmp;
			std::getline(res, tmp);
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

MeshResource::MeshResource(ResourceFile&& filename) {
	readFile(std::move(filename));
	initMesh();
}
