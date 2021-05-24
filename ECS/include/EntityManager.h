#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <ranges>

#include "Entity.h"
#include "Component.h"
#include "ComponentHandle.h"
#include "utils.h"

class EntityManager {
	std::vector<Entity*> _entities;
	std::unordered_map<Component::Id, std::vector<Component*>> _componentsTable;

	template <typename T, typename ...Args>
	requires std::derived_from<T, ComponentData<T>>
	T& addComponent(Entity& entity, Args&& ...args) {
		T* component = new T(std::forward<Args>(args)...);
		component->_entity = &entity;
		_componentsTable.try_emplace(T::Type);
		if (_componentsTable[T::Type].size() <= entity._id)
			_componentsTable[T::Type].resize(Entity::_count, nullptr);
		_componentsTable[T::Type][entity._id] = component;
		return *component;
	}

public:
	EntityManager() = default;

	~EntityManager();

	[[nodiscard]] const std::vector<Entity*>& GetEntities() const;

	template <std::derived_from<Component> ...Args>
	auto GetEntitiesBy() {
		constexpr auto count = sizeof...(Args);
		const auto types = std::make_tuple(Args::Type...);

		std::vector<ComplexComponent<Args...>> result;
		const auto first = std::get<0>(types);
		if (!_componentsTable.contains(first)) return result;

		for (Component* item: _componentsTable.at(first)) {
			if (item == nullptr) continue;

			ComplexComponent<Args...> complex;
			bool consideredToAdd = true;

			complex.Entity = &item->GetEntity();
			foreach([&](const auto i) {
				typename std::tuple_element<i, std::tuple<Args...>>::type T;
				const auto type = std::get<i>(types);

				if (!_componentsTable.contains(type)) {
					consideredToAdd = false;
				}
				else {
					const std::vector<Component*>& components = _componentsTable.at(type);
					if ((components.size() <= complex.Entity->_id
							|| components.at(complex.Entity->_id) == nullptr))
						consideredToAdd = false;
					std::get<i>(complex.Components) = static_cast<decltype(T)*>(components
							.at(complex.Entity->_id));
				}
			}, std::make_integer_sequence<const std::size_t, count>());

			if (consideredToAdd)
				result.push_back(complex);
		}
		return result;
	}

	Entity& CreateEntity();

	Entity& Instantiate(const Entity& parent);

	template <typename T>
	requires std::derived_from<T, ComponentData<T>>
	ComponentHandle<T> GetComponent(const Entity& entity) const {
		if (!_componentsTable.contains(T::Type))
			return nullptr;
		const auto& components = _componentsTable.at(T::Type);
		if (components.size() <= entity._id)
			return nullptr;
		if (components.at(entity._id) == nullptr)
			return nullptr;
		return static_cast<T&>(*components.at(entity._id));
	}

	template <typename T>
	requires std::derived_from<T, ComponentData<T>>
	T& GetOrAddComponent(Entity& actor, std::function<T()> f) {
		auto cmp = GetComponent<T>(actor);
		if (!cmp)
			return addComponent<T>(actor, f());
		return *cmp;
	}

	template <typename T, typename ...Args>
	requires std::derived_from<T, ComponentData<T>> && (!std::is_default_constructible_v<T>)
	T& GetOrAddComponent(Entity& actor, Args&& ... args) {
		return GetOrAddComponent<T>(actor, [&args...] {
			return T(std::forward<Args>(args)...);
		});
	}

	template <typename T>
	requires std::derived_from<T, ComponentData<T>> && std::is_default_constructible_v<T>
	T& GetOrAddComponent(Entity& entity, std::function<void(T&)> f) {
		return GetOrAddComponent<T>(entity, [f] {
			auto component = T();
			f(component);
			return component;
		});
	}

	template <typename T>
	requires std::derived_from<T, ComponentData<T>> && std::is_default_constructible_v<T>
	T& GetOrAddComponent(Entity& entity) {
		return GetOrAddComponent<T>(entity, [] { return T(); });
	}

	template <typename T>
	requires std::derived_from<T, ComponentData<T>>
	bool RemoveComponent(const Entity& entity) {
		if (!HasComponent<T>(entity))
			return false;
		delete _componentsTable[T::Type][entity._id];
		_componentsTable[T::Type][entity._id] = nullptr;

		return true;
	}

	template <typename T>
	requires std::derived_from<T, ComponentData<T>>
	[[nodiscard]] bool HasComponent(const Entity& entity) const {
		return GetComponent<T>(entity) != nullptr;
	}

	template <typename T, typename ...Args>
	requires std::derived_from<T, ComponentData<T>>
	T& ReplaceComponent(Entity& entity, Args&& ... args) {
		return RemoveComponent<T>(entity) ? addComponent<T>(entity, args...) :
				GetComponent<T>(entity);
	}

	void DestroyEntity(const Entity& entity);
};
