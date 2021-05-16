#include "ShaderResource.h"
#include <fstream>
#include <string>

#include <sstream>

constexpr auto BUFFER = 2048;

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

GLuint ShaderResource::LoadShader(GLuint type) {
	const std::string& shaderProgram = LoadShaderFile(std::move(Name()));
	const char* text = shaderProgram.c_str();
	const GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &text, nullptr);
	glCompileShader(shader);

	return shader;
}

VertexShaderResource::VertexShaderResource(std::string&& shaderName) : ShaderResource(shaderName + ".vert")
{
}

FragmentShaderResource::FragmentShaderResource(std::string&& shaderName) : ShaderResource(shaderName + ".frag")
{
}
