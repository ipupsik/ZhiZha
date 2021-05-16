#pragma once

#include "Material.h"
//#include "ResourceManager.h"

Material::Material()
{
}

void Material::attachVertexShader(std::string&& filename)
{
	//VertexShader = ResourceManager::Current.GetOrAddResource<VertexShaderResource>(std::move(filename));
}

void Material::attachFragmentShader(std::string&& filename)
{
	//FragmentShader = ResourceManager::Current.GetOrAddResource<FragmentShaderResource>(std::move(filename));
}

void Material::attachTexture(std::string&& filename)
{
	//Textures.push_back(ResourceManager::Current.GetOrAddResource<TextureResource>(std::move(filename)));
}