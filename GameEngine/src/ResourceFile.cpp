#include "ResourceFile.h"

#include <sstream>

ResourceFile::ResourceFile(std::string&& filename): _filename("../share/" + filename) {
	if (!sf::FileInputStream::open(_filename))
		throw std::runtime_error("Cannot open '" + _filename + "'");
	std::ifstream::open(_filename);
}

std::string& ResourceFile::Name() {
	return _filename;
}