#include "ShaderResource.h"
#include <fstream>
#include <string>

#include <sstream>

const std::string& LoadShaderFile(std::string&& filename)
{
	std::string s = "Materials/";
	s += filename;
	std::ifstream ifile(s, std::ifstream::binary);
	std::string filetext;

	while (ifile.good()) {
		std::string line;
		std::getline(ifile, line);
		filetext.append(line + "\n");
	}

	return filetext;
}

void ShaderResource::LoadShader(GLuint type) {
	const std::string& shaderProgram = LoadShaderFile(std::move(Name()));
	const char* text = shaderProgram.c_str();
	_shaderId = glCreateShader(type);
	glShaderSource(_shaderId, 1, &text, nullptr);
	glCompileShader(_shaderId);
}

VertexShaderResource::VertexShaderResource(std::string&& shaderName) : ShaderResource(shaderName + ".vert")
{
}

void VertexShaderResource::LoadShader(GLuint type)
{
	ShaderResource::LoadShader(GL_VERTEX_SHADER);
}

FragmentShaderResource::FragmentShaderResource(std::string&& shaderName) : ShaderResource(shaderName + ".frag")
{
}

void FragmentShaderResource::LoadShader(GLuint type)
{
	ShaderResource::LoadShader(GL_FRAGMENT_SHADER);
}
