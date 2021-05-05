#include <SFML/Graphics.hpp>
#include <cassert>

#include "ActorManager.h"

int main() {
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
}
