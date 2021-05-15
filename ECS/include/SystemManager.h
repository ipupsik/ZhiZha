#pragma once

#include <concepts>
#include <unordered_map>
#include <execution>

#include "System.h"

class SystemManager {
	SystemManager() = default;
	
	std::unordered_map<std::size_t, std::vector<std::shared_ptr<System>>> _systemsTable;

	template<typename S, typename T>
	void tryInsertAs(std::shared_ptr<T> system) {
		const auto& type = TypeFamily<System>::Type<S>();
		
		if constexpr (std::is_base_of_v<S, T>) {
			_systemsTable.try_emplace(type);
			_systemsTable.at(type).emplace_back(system);
		}
	}

public:
	static SystemManager Current;
	
	SystemManager(const SystemManager&) = delete;
	SystemManager& operator=(const SystemManager&) = delete;
	SystemManager(SystemManager&&) = delete;
	SystemManager& operator=(SystemManager&&) = delete;

	template <typename T, typename ...Args>
		requires std::derived_from<T, System>
	SystemManager& RegisterSystem(Args&&... args) {
		auto system = std::make_shared<T>(std::forward<Args>(args)...);

		tryInsertAs<PostInitSystem>(system);
		tryInsertAs<UpdateSystem>(system);
		tryInsertAs<FixedUpdateSystem>(system);
		tryInsertAs<PostUpdateSystem>(system);
		tryInsertAs<InitSystem>(system);
		
		return *this;
	}

	void PostInit() const;

	void Update() const;

	void FixedUpdate() const;

	void PostUpdate() const;

	void Init() const;
};
