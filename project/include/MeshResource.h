#include <string>
#include <vector>

#include "SFML/System/Vector2.hpp"

class MeshResource {
	struct Face {
		unsigned int v1, v2, v3;
	};
	
	std::vector<sf::Vector2f> _vertices;
	std::vector<sf::Vector2f> _normals;
	std::vector<sf::Vector2f> _uvs;
	std::vector<sf::Vector2f> _uvsInit;

	std::vector<Face> _faces;
	std::vector<Face > _facesNormal;
	std::vector<Face> _facesTexCoord;

	unsigned int _indexEBO, _indexVBO, _indexTexVBO, _indexVAO;

	void readFile(std::string&& filename);

	void initMesh();

public:
	explicit MeshResource(std::string&& filename);
};
