#include "ResourceManager.h"

ResourceManager::~ResourceManager() {
	for (const auto& [_, v] : _resourcesTable)
		delete v;
}
