#include <SFML/Graphics.hpp>
#include <cassert>

#include "ActorManager.h"

using sf::Window;
using sf::Event;
using sf::VideoMode;

int main() {
    auto ch = ActorManager::Current.CreateActor();
    auto ch2 = ActorManager::Current.Instantiate(ch);
    auto some = ActorManager::Current.GetActorsBy<TransformComponent>();

    assert(some.size() == 2);
    assert(*some.begin() == ch2);
    assert(ch2 != ch);
    assert(ch2->GetParent().lock() == ch);
    assert((ch->Transform()->Scale == sf::Vector2f{1, 1}));

    ActorManager::Current.GetOrAddComponent<TestComponent>(ch2, TestComponent(1));
    assert(ch2->GetOrAddComponent<TestComponent>(TestComponent(2))->Data == 1);
    auto ch3 = ActorManager::Current.GetActorsBy<TestComponent>();
    assert(ch3.size() == 1);
    ch2->RemoveComponent<TestComponent>();
    assert(!ch2->GetComponent<TestComponent>());
}