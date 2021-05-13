#pragma once

#include <fstream>

class ResourceFile: public std::basic_ifstream<char> {
	std::string _filename;
	std::string _content;
	bool _isLoaded = false;

public:
	ResourceFile(const ResourceFile&) = delete;
	ResourceFile& operator=(const ResourceFile&) = delete;
	ResourceFile(ResourceFile&&) = default;
	ResourceFile& operator=(ResourceFile&&) = default;
	
	ResourceFile(std::string&& filename);
	ResourceFile(const char* const filename): ResourceFile(std::string(filename)) {}

	std::string& Name();

	const std::string& LoadContent();

	void UnloadContent();
};
