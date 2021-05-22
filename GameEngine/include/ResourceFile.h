#pragma once

#include <SFML/System/FileInputStream.hpp>
#include <fstream>

class ResourceFile: public virtual sf::FileInputStream, public std::ifstream {
	std::string _filename;

public:
	ResourceFile(const ResourceFile&) = delete;
	ResourceFile& operator=(const ResourceFile&) = delete;
	ResourceFile(ResourceFile&&) = delete;
	ResourceFile& operator=(ResourceFile&&) = delete;
	
	explicit ResourceFile(std::string&& filename);
	explicit ResourceFile(const char* const filename): ResourceFile(std::string(filename)) {}

	std::string& Name();

	//virtual void LoadContent() = 0;

	//virtual void UnloadContent() = 0;
};
