#include "ShaderResource.h"
#include <fstream>
#include <string>

GLuint LoadShader(ResourceFile& resource, GLuint type) {
	const std::string& shaderProgram = resource.LoadContent();
	const char* text = shaderProgram.c_str();
	const GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &text, nullptr);
	glCompileShader(shader);

	return shader;
}

ShaderResource::ShaderResource(std::string&& shaderName) {
	ResourceFile fragmentShader(shaderName + ".frag");
	ResourceFile vertexShader(shaderName + ".vert");
	GLuint fragShader = LoadShader(fragmentShader, GL_FRAGMENT_SHADER);
	GLuint vertShader = LoadShader(vertexShader, GL_VERTEX_SHADER);

	GLint ok;
	GLchar log[2000] = {};
	_shaderId = glCreateProgram();
	glAttachShader(_shaderId, fragShader);
	glAttachShader(_shaderId, vertShader);
	glLinkProgram(_shaderId);
	glGetProgramiv(_shaderId, GL_LINK_STATUS, &ok);
	if (!ok) {
		glGetProgramInfoLog(_shaderId, 2000, nullptr, log);
		printf("\n");
	}
}
