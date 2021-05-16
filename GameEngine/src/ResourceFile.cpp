#include "../include/ResourceFile.h"

#include <sstream>

constexpr auto BUFFER = 2048;

ResourceFile::ResourceFile(std::string&& filename): _filename("../share/" + filename) {
	
}

std::string& ResourceFile::Name() {
	return _filename;
}

//void ResourceFile::LoadContent() {
//	if (!_isLoaded) {
//		std::stringstream ss;
//		while (!eof()) {
//			char buff[BUFFER] = {};
//			read(buff, BUFFER);
//			ss << buff;
//		}
//		_isLoaded = true;
//		_content = ss.str();
//	}
//}
//
//void ResourceFile::UnloadContent() {
//	if (_isLoaded)
//		_content.clear();
//	_isLoaded = false;
//}
