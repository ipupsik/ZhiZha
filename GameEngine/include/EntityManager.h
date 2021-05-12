#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <ranges>

#include "Entity.h"
#include "Component.h"
#include "ComponentHandle.h"

class EntityManager {
	std::vector<Entity*> _entities;
	std::unordered_map<Component::Id, std::vector<Component*>> _componentsTable;

	EntityManager();

	template <typename T, typename ...Args>
		requires std::derived_from<T, ComponentData<T>>
	T& addComponent(Entity& entity, Args&&...args) {
		T* component = new T(std::forward<Args>(args)...);
		component->EntityId = entity._id;
		++entity._componentsCount;
		_componentsTable.try_emplace(T::Type);
		if (_componentsTable[T::Type].size() <= entity._id)
			_componentsTable[T::Type].resize(Entity::_count, nullptr);
		_componentsTable[T::Type][entity._id] = component;
		return *component;
	}

public:
	~EntityManager();

	[[nodiscard]] const std::vector<Entity*>& GetEntities() const;

  template<typename T>
  requires std::derived_from<T, ComponentData<T>>
  auto GetEntitiesBy() {
      _componentsTable.try_emplace(T::Type);
      return _componentsTable.at(T::Type) | std::ranges::views::filter([](Component *component) {
        return component != nullptr;
      }) | std::ranges::views::transform([this](Component *component) {
        return *_entities.at(component->EntityId);
      });
  }

	Entity CreateEntity();

	Entity Instantiate(const Entity& parent);

	template <typename T>
		requires std::derived_from<T, ComponentData<T>>
	ComponentHandle<T> GetComponent(const Entity& entity) const {
		if (!_componentsTable.contains(T::Type))
			return nullptr;
		const auto& components = _componentsTable.at(T::Type);
		if (components.size() < entity._id || components.at(entity._id) == nullptr)
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
	T& GetOrAddComponent(Entity& actor, Args&&... args) {
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
	bool RemoveComponent(Entity& entity) {
		if (!HasComponent<T>(entity)) return false;
		delete _componentsTable[T::Type][entity._id];
		_componentsTable[T::Type][entity._id] = nullptr;

		--entity._componentsCount;
		return true;
	}

	template <typename T>
		requires std::derived_from<T, ComponentData<T>>
	[[nodiscard]] bool HasComponent(const Entity& entity) const {
		return GetComponent<T>(entity) != nullptr;
	}

	template <typename T, typename ...Args>
		requires std::derived_from<T, ComponentData<T>>
	T& ReplaceComponent(Entity& entity, Args&&... args) {
		return RemoveComponent<T>(entity) ? addComponent<T>(entity, args...) : GetComponent<T>(entity)->get();
	}

	static EntityManager Current;
};
