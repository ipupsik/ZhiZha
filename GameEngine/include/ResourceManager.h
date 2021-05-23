#pragma once

#include <concepts>
#include <unordered_map>
#include <execution>
#include "TypeFamily.h"
#include "ResourceFile.h"

class ResourceManager {
	std::unordered_map<std::size_t, std::unordered_map<std::string, ResourceFile*>> _resourcesTable;

public:
	ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	~ResourceManager();

	template<std::derived_from<ResourceFile> T>
	T* GetOrAddResource(std::string filename) {
		auto type = TypeFamily<ResourceFile>::Type<T>();
		if (_resourcesTable.contains(type) && _resourcesTable[type].contains(filename))
			return static_cast<T*>(_resourcesTable[type][filename]);
		
		auto newResource = new T(std::forward<std::string&&>(filename));
		_resourcesTable.try_emplace(type);
		_resourcesTable[type][filename] = newResource;
		return newResource;
	}
};