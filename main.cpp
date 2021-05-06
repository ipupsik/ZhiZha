#include <SFML/Graphics.hpp>
#include <cassert>

#include "ActorManager.h"
#include "utils.h"

using namespace sf::Extensions::Vector2;

int main() {
	const auto& foo = sf::Vector2f{0, 1};
	const auto& baz = sf::Vector2f{1, 0};
	const auto& bam = sf::Vector2i{1, 1};

	const auto& bar = bam->*Length<int>();

	const auto ch = ActorManager::Current.CreateActor();
	ActorManager::Current.GetOrAddComponent<NameComponent>(ch, NameComponent("ch"));
	const auto ch2 = ActorManager::Current.Instantiate(ch);
	ActorManager::Current.GetOrAddComponent<NameComponent>(ch2, NameComponent("ch2"));
	const auto some = ActorManager::Current.GetActorsBy<TransformComponent>();

	assert(some.size() == 2);
	assert(ch2 != ch);
	assert(ch2->GetParent().lock() == ch);
	assert((ch->Transform()->Scale == sf::Vector2f{1, 1}));

	ActorManager::Current.GetOrAddComponent<TestComponent>(ch2, TestComponent(1));
	assert(ActorManager::Current.GetOrAddComponent<TestComponent>(ch2, TestComponent(2))->Data == 1);
	const auto ch3 = ActorManager::Current.GetActorsBy<TestComponent>();
	assert(ch3.size() == 1);
	ActorManager::Current.RemoveComponent<TestComponent>(*ch3.begin());
	assert(!ActorManager::Current.GetComponent<TestComponent>(*ch3.begin()));
    assert(!ActorManager::Current.RemoveComponent<TestComponent>(*ch3.begin()));

	sleep(sf::seconds(10));
}
