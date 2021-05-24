#include "ResourceManager.h"

ResourceManager::~ResourceManager() {
	for (const auto& [_, v] : _resourcesTable)
		for (const auto& [_, vv] : v)
			delete vv;
}
