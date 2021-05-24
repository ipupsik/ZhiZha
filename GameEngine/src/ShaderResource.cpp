#include "ShaderResource.h"
#include <fstream>
#include <string>

#include <sstream>

ShaderResource::ShaderResource(std::string&& shaderName) : ResourceFile(std::move(shaderName))
{
}

std::string LoadShaderFile(std::string& filename)
{
	std::ifstream ifile(filename, std::ifstream::binary);
	std::string filetext;

	while (ifile.good()) {
		std::string line;
		std::getline(ifile, line);
		filetext.append(line + "\n");
	}

	return filetext;
}

void ShaderResource::LoadShader(GLuint type) {
	const std::string shaderProgram(LoadShaderFile(Name()));
	const char* text = shaderProgram.c_str();
	_shaderId = glCreateShader(type);
	glShaderSource(_shaderId, 1, &text, nullptr);
	glCompileShader(_shaderId);
}

VertexShaderResource::VertexShaderResource(std::string&& shaderName) : ShaderResource(shaderName + ".vert")
{
	ShaderResource::LoadShader(GL_VERTEX_SHADER);
}

FragmentShaderResource::FragmentShaderResource(std::string&& shaderName) : ShaderResource(shaderName + ".frag")
{
	ShaderResource::LoadShader(GL_FRAGMENT_SHADER);
}