#include "ShaderResource.h"
#include <fstream>
#include <string>

#include <sstream>

ShaderResource::ShaderResource(std::string shaderName, sf::Shader::Type type)
		:ResourceFile(std::move(shaderName)) {
	if (!_shader.loadFromStream(*this, type))
		throw std::runtime_error("Cannot load shader " + Name());
}

ShaderResource::ShaderResource(const std::string& name)
		:ResourceFile(name + ".vert") {
	auto fragmentShader = ResourceFile(name + ".frag");
	if (!_shader.loadFromStream(*this, fragmentShader))
		throw std::runtime_error("Cannot load shaders " + name);
}

VertexShaderResource::VertexShaderResource(std::string&& shaderName)
		:ShaderResource(shaderName + ".vert", sf::Shader::Vertex) { }

FragmentShaderResource::FragmentShaderResource(std::string&& shaderName)
		:ShaderResource(shaderName + ".frag", sf::Shader::Fragment) { }