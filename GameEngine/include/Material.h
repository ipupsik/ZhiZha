#pragma once

#include "../lib/glad/include/glad/glad.h"

class Material
{
public:
	void InitShaders(const char* filename);
	void SetProgram();
	void ResetProgram();
	GLuint prog;
};
