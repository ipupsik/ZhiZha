#include "EntityManager.h"

EntityManager EntityManager::Current = EntityManager();

Entity& EntityManager::Instantiate(const Entity& parent) {
	auto copy = parent.copy();
	if (_entities.size() <= copy->_id)
		_entities.resize(Entity::_count);
	_entities[copy->_id] = copy;

	for (auto& [_, v] : _componentsTable) {
		if (v.size() <= parent._id || v.size() <= copy->_id)
			v.resize(Entity::_count, nullptr);
		if (v[parent._id] != nullptr)
			v[copy->_id] = v[parent._id]->Copy();
	}
	return *copy;
}

Entity& EntityManager::CreateEntity() {
	const auto basic = new Entity();
	if (_entities.size() <= basic->_id)
		_entities.resize(Entity::_count);
	_entities[basic->_id] = basic;
	return *basic;
}

EntityManager::~EntityManager() {	
	for (const auto& [_, v] : _componentsTable)
		for (auto component : v)
			delete component;
	for (auto entity : _entities)
		delete entity;
}

const std::vector<Entity*>& EntityManager::GetEntities() const {
	return _entities;
}

EntityManager::EntityManager() = default;
