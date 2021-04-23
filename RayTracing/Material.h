#ifndef _H_MATERIAL_
#define _H_MATERIAL_

#include <glad/glad.h>

class Material
{
public:
	void InitShaders(const char* filename);
	void SetProgram();
	void ResetProgram();
	GLuint prog;
};

#endif
