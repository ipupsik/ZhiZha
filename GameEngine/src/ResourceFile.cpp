#include "ResourceFile.h"

#include <sstream>

ResourceFile::ResourceFile(std::string&& filename): _filename("../share/" + filename) {
	if (!open(_filename))
		throw std::runtime_error("Cannot open '" + _filename + "'");
}

std::string& ResourceFile::Name() {
	return _filename;
}