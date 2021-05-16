#pragma once

#include <concepts>
#include <unordered_map>
#include <execution>

#include "ResourceFile.h"

class ResourceManager {
	ResourceManager() = default;

	std::unordered_map<std::string, ResourceFile*> _resourcesTable;

public:

	template <typename T>
	requires std::derived_from<T, ResourceFile>
	T* GetOrAddResource(std::string&& filename) {
		if (_resourcesTable.find(filename) != _resourcesTable.end())
			return dynamic_cast<T*>(_resourcesTable.at(filename));
		else
		{
			T* newResource = new T(std::move(filename));
			_resourcesTable.insert({ filename, newResource });
			return dynamic_cast<T*>(newResource);
		}
	}

	static ResourceManager Current;
};