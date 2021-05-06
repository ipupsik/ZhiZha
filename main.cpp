#include <SFML/Graphics.hpp>
#include <cassert>

#include "ActorManager.h"
#include "utils.h"

using namespace sf::Extensions::Vector2;

int main() {
    auto manager = ActorManager::Current;
    auto archetype = ActorArchetype({
        new TestComponent(4)
    });

	auto ch = manager.FromArchetype(std::move(archetype));
	auto ch2 = manager.Instantiate(ch);

    assert(ch2.GetParent() == &ch);

	assert(manager.HasComponent<TestComponent>(ch));
    assert(manager.HasComponent<TestComponent>(ch2));

    manager.GetComponent<TestComponent>(ch)->Data = 3;

    assert(manager.GetComponent<TestComponent>(ch)->Data == 3);
    assert(manager.GetComponent<TestComponent>(ch2)->Data == 4);

    manager.GetOrAddComponent<NameComponent>(ch2, NameComponent("ch2"));

    assert(!manager.HasComponent<NameComponent>(ch));
    assert(manager.HasComponent<NameComponent>(ch2));

    manager.GetOrAddComponent(ch2, NameComponent("hmm"));

    assert(manager.GetComponent<NameComponent>(ch2)->Name == "ch2");

    manager.RemoveComponent<NameComponent>(ch2);

    assert(!manager.HasComponent<NameComponent>(ch2));

    auto named = manager.GetActorsBy<NameComponent>();

    assert(named.size() == 1);
    assert(named.contains(ch2));

    auto all = manager.GetActors();

    assert(all.size() == 3);
}
