#pragma once

#include <fstream>

class ResourceFile: public std::basic_ifstream<char> {
	std::string _filename;
	bool _isLoaded = false;

public:
	ResourceFile(const ResourceFile&) = delete;
	ResourceFile& operator=(const ResourceFile&) = delete;
	ResourceFile(ResourceFile&&) = delete;
	ResourceFile& operator=(ResourceFile&&) = default;
	
	ResourceFile(std::string&& filename);
	ResourceFile(const char* const filename): ResourceFile(std::string(filename)) {}

	std::string& Name();

	//virtual void LoadContent() = 0;

	//virtual void UnloadContent() = 0;
};
