#pragma once

#include <SFML/System.hpp>

class Material
{
public:
	void InitShaders(const char* filename);
	void SetProgram();
	void ResetProgram();
	sf::Uint32 prog;
};
