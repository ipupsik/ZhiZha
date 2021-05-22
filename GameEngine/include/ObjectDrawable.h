#pragma once

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/System/Vector3.hpp"

#include <utility>

class ObjectDrawable : public sf::Drawable {
	friend class MeshResource;

	std::vector<sf::Vector2f> _vertices;
	std::vector<sf::Vector2f> _uvs;

	std::vector<sf::Vector3<unsigned int>> _faces;

	GLuint _indexEBO = -1, _indexVBO = -1, _indexVAO = -1, _indexTexVBO = -1;

	void init();
	void loadData(std::vector<sf::Vector2f> vertices,
			std::vector<sf::Vector2f> uvs,
			std::vector<sf::Vector3<unsigned int>> faces);
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};