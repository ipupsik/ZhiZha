#pragma once

#include <concepts>
#include <unordered_map>
#include <execution>

#include "ResourceFile.h"

class ResourceManager {
	std::unordered_map<std::string, ResourceFile*> _resourcesTable;

public:
	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

	ResourceFile& GetOrAddResource(std::string&& filename) {
		if (_resourcesTable.find(filename) != _resourcesTable.end())
			return *_resourcesTable[filename];
		else
		{
			auto* newResource = new ResourceFile(std::move(filename));
			_resourcesTable[newResource->Name()] = newResource;
			return *newResource;
		}
	}
};