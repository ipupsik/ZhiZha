#include "ResourceFile.h"

#include <sstream>

ResourceFile::ResourceFile(std::string&& filename): _filename("../share/" + filename) {
	
}

std::string& ResourceFile::Name() {
	return _filename;
}
