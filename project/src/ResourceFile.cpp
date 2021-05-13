#include "ResourceFile.h"

#include <sstream>

constexpr auto BUFFER = 2048;

ResourceFile::ResourceFile(std::string&& filename): _filename("../share/" + filename) {
	open(_filename, std::ios::binary | std::ios::in);
	if (!is_open())
		throw std::runtime_error("Cannot open " + _filename + " as resource");
}

std::string& ResourceFile::Name() {
	return _filename;
}

const std::string& ResourceFile::LoadContent() {
	if (!_isLoaded) {
		std::stringstream ss;
		while (!eof()) {
			char buff[BUFFER] = {};
			read(buff, BUFFER);
			ss << buff;
		}
		_isLoaded = true;
		_content = ss.str();
	}
	return _content;
}

void ResourceFile::UnloadContent() {
	if (_isLoaded)
		_content.clear();
	_isLoaded = false;
}
