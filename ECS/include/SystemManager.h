#pragma once

#include <concepts>
#include <execution>

#include "System.h"

class SystemManager {
	std::vector<UpdateSystem*> _updates;
	std::vector<PostUpdateSystem*> _postUpdates;
	std::vector<FixedUpdateSystem*> _fixedUpdates;
	std::vector<InitSystem*> _inits;
	std::vector<PostInitSystem*> _postInits;
	EntityManager& _inner;

public:
	SystemManager(EntityManager& inner): _inner(inner) {}
	
	SystemManager(const SystemManager&) = delete;
	SystemManager& operator=(const SystemManager&) = delete;
	SystemManager(SystemManager&&) = delete;
	SystemManager& operator=(SystemManager&&) = delete;
	~SystemManager();

	template <typename T, typename ...Args>
	requires std::derived_from<T, System>
	SystemManager& RegisterSystem(T* system) {
		system->_entities = &_inner;
		
		if constexpr (std::is_base_of_v<UpdateSystem, T>)
			_updates.emplace_back(system);
		if constexpr (std::is_base_of_v<PostUpdateSystem, T>)
			_postUpdates.emplace_back(system);
		if constexpr (std::is_base_of_v<FixedUpdateSystem, T>)
			_fixedUpdates.emplace_back(system);
		if constexpr(std::is_base_of_v<InitSystem, T>)
			_inits.emplace_back(system);
		if constexpr (std::is_base_of_v<PostInitSystem, T>)
			_postInits.emplace_back(system);

		return *this;
	}

	void PostInit() const;

	void Update() const;

	void FixedUpdate() const;

	void PostUpdate() const;

	void Init() const;
};
