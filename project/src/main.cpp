#include <SFML/Graphics.hpp>
#include <cassert>

#include "EntityManager.h"
#include "utils.h"
#include "Components.h"

using namespace sf::Extensions::Vector2;

int main() {
	auto manager = EntityManager::Current;

	auto ch = manager.CreateEntity();
	auto test = TestComponent();
	test.Data = 4;
	manager.GetOrAddComponent(ch, test);
	auto ch2 = manager.Instantiate(ch);

	assert(ch2.GetParent() == ch);

	assert(manager.HasComponent<TestComponent>(ch));
	assert(manager.HasComponent<TestComponent>(ch2));

	manager.GetComponent<TestComponent>(ch)->get().Data = 3;

	assert(manager.GetComponent<TestComponent>(ch)->get().Data == 3);
	assert(manager.GetComponent<TestComponent>(ch2)->get().Data == 4);

	auto name = NameComponent();
	name.Name = "ch2";
	manager.GetOrAddComponent(ch2, name);

	assert(!manager.HasComponent<NameComponent>(ch));
	assert(manager.HasComponent<NameComponent>(ch2));

	manager.GetOrAddComponent(ch2, NameComponent());

	assert(manager.GetComponent<NameComponent>(ch2)->get().Name == "ch2");

	name.Name = "test";

	manager.ReplaceComponent<NameComponent>(ch2, name);

	assert(manager.GetComponent<NameComponent>(ch2)->get().Name == "test");

	const auto named = manager.GetEntitiesBy<NameComponent>();

	assert(named.size() == 1);

	manager.RemoveComponent<NameComponent>(ch2);

	assert(!manager.HasComponent<NameComponent>(ch2));

	const auto all = manager.GetEntities();

	assert(all.size() == 2);
}
