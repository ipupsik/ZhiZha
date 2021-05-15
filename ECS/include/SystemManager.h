#pragma once

#include <concepts>
#include <unordered_map>
#include <execution>

#include "System.h"

class SystemManager {
	SystemManager() = default;

	std::vector<UpdateSystem*> _updates;
	std::vector<PostUpdateSystem*> _postUpdates;
	std::vector<FixedUpdateSystem*> _fixedUpdates;
	std::vector<InitSystem*> _inits;
	std::vector<PostInitSystem*> _postInits;

public:
	static SystemManager Current;

	SystemManager(const SystemManager&) = delete;
	SystemManager& operator=(const SystemManager&) = delete;
	SystemManager(SystemManager&&) = delete;
	SystemManager& operator=(SystemManager&&) = delete;

	template <typename T, typename ...Args>
	requires std::derived_from<T, System>
	SystemManager& RegisterSystem(Args&& ... args) {
		T* system = new T(std::forward<Args>(args)...);

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
