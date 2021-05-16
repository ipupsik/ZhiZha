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
	~ResourceManager();

	template<std::derived_from<ResourceFile> T>
	T& GetOrAddResource(std::string&& filename) {
		if (!_resourcesTable.contains(filename))
			return static_cast<T*>(_resourcesTable[filename]);
		
		auto* newResource = new T(std::move(filename));
		_resourcesTable[newResource->Name()] = newResource;
		return *newResource;
	}
};