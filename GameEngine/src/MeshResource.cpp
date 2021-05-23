#include "MeshResource.h"

#include <iostream>
#include "ObjectDrawable.h"

void MeshResource::readFile() {
	std::string s;
	auto& fin = *this;
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

MeshResource::MeshResource(std::string&& filename)
		:ResourceFile(std::move(filename + ".obj")) {
	readFile();
	_obj.loadData(_vertices, _uvs, _faces);
	_obj.init();
}