#include "EntityManager.h"

Entity& EntityManager::Instantiate(const Entity& parent) {
	auto copy = parent.copy();
	if (_entities.size() <= copy->_id)
		_entities.resize(Entity::_count);
	_entities[copy->_id] = copy;

#pragma unroll 10
	for (auto&[_, v] : _componentsTable) {
		if (v.size() <= parent._id || v.size() <= copy->_id)
			v.resize(Entity::_count, nullptr);
		if (v[parent._id] != nullptr) {
			v[copy->_id] = v[parent._id]->Copy();
			v[copy->_id]->_entity = copy;
		}
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
	for (const auto&[_, v] : _componentsTable)
#pragma unroll 10
		for (auto component : v)
			delete component;
#pragma unroll 10
	for (auto entity : _entities)
		delete entity;
}

const std::vector<Entity*>& EntityManager::GetEntities() const {
	return _entities;
}

void EntityManager::DestroyEntity(const Entity& entity) {
#pragma unroll 10
	for (auto&[k, v] : _componentsTable)
		if (v.size() > entity._id) {
			v[entity._id] = nullptr;
			delete v[entity._id];
		}
	_entities[entity._id] = nullptr;
	delete _entities[entity._id];
}
