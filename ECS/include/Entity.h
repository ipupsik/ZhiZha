#pragma once

#include <atomic>
#include <memory>
#include <unordered_map>

class Entity {
public:
	using Id = std::size_t;

private:
	friend class EntityManager;
	friend struct std::hash<Entity>;

	const Entity* _parent;
	const Id _id;
	bool _isActive = true;

	static std::atomic_size_t _count;

	[[nodiscard]] Entity* copy() const;

public:
	Entity();
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	friend bool operator==(const Entity& lhs, const Entity& rhs) {
		return lhs._id == rhs._id;
	}

	bool operator<(const Entity& rhs) const;

	[[nodiscard]] const Entity* GetParent() const;
	[[nodiscard]] bool IsActive() const { return _isActive; }
	void SetActive(bool active = true) { _isActive = active; }
};

template <>
struct std::hash<Entity> {
	size_t operator()(const Entity& actor) const noexcept {
		return std::hash<std::size_t>{}(actor._id);
	}
};
