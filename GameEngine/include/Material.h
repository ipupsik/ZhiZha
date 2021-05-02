#pragma once

#include <SFML/System.hpp>

class Material
{
public:
	void InitShaders(const sf::String &filename);
	void SetProgram();
	void ResetProgram();
	sf::Uint32 prog;
};
