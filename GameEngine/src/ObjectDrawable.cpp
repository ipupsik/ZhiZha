#include <iostream>
#include "glad/glad.h"
#include "ObjectDrawable.h"
#include "SFML/Graphics.hpp"

void ObjectDrawable::init() {
	glGenBuffers(1, &_indexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _indexVBO);
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(sf::Vector2f) * _vertices.size(), _vertices.data(),
				GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &_indexTexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _indexTexVBO);
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(sf::Vector2f) * _uvs.size(), _uvs.data(),
				GL_STATIC_DRAW);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &_indexEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexEBO);
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sf::Vector3<unsigned int>) * _faces.size(),
				_faces.data(), GL_STATIC_DRAW);
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

void ObjectDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//	auto& shader = const_cast<>
//	states.shader->setUniform("Transform")

	glBindVertexArray(_indexVAO);
	{
		for (int i = 0; i < 2; i++)
			glEnableVertexAttribArray(i);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexEBO);
		{
			glDrawElements(GL_TRIANGLES, 3 * _faces.size(), GL_UNSIGNED_INT, nullptr);
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		for (int i = 1; i >= 0; i--)
			glDisableVertexAttribArray(i);
	}
}

void ObjectDrawable::loadData(std::vector<sf::Vector2f> vertices, std::vector<sf::Vector2f> uvs,
		std::vector<sf::Vector3<unsigned int>> faces) {
	_vertices = std::move(vertices);
	_uvs = std::move(uvs);
	_faces = std::move(faces);
}
