#include "MeshResource.h"

#include <iostream>

void MeshResource::readFile() {
	std::string s = Name();
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
			sf::Vector3<unsigned int> f, n, uv;

			fin >> f.x;
			fin >> symbol;
			fin >> uv.x;
			fin >> symbol;
			fin >> n.x;

			fin >> f.y;
			fin >> symbol;
			fin >> uv.y;
			fin >> symbol;
			fin >> n.y;

			fin >> f.z;
			fin >> symbol;
			fin >> uv.z;
			fin >> symbol;
			fin >> n.z;

			f.x--;
			f.y--;
			f.z--;

			uv.x--;
			uv.y--;
			uv.z--;

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
		_uvs[_faces[i].x] = _uvsInit[_facesTexCoord[i].x];
		_uvs[_faces[i].y] = _uvsInit[_facesTexCoord[i].y];
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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sf::Vector3<unsigned int>) * _faces.size(), &*_faces.begin(), GL_STATIC_DRAW);
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
	readFile();
	initMesh();
}

MeshResource::MeshResource()
{

}