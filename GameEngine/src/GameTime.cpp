#include "GameTime.h"

#include "SFML/System/Sleep.hpp"

void GameTime::waitForUpdate() {
	_frameCount++;

	_deltaTime = _timeClock.getElapsedTime().asSeconds();

	if (_maxDeltaTime > _deltaTime)
		sf::sleep(sf::seconds(_maxDeltaTime - _deltaTime));

	const auto temp = _timeClock.getElapsedTime().asSeconds();
	_time += temp;
	_deltaTime = temp;
	_deltaTimeQueue.push_back(_deltaTime);
	if (_deltaTimeQueue.size() > 60)
		_deltaTimeQueue.pop_front();

	_timeClock.restart();
}

void GameTime::waitForFixedUpdate() {
	_fixedFrameTime = _fixedTimeClock.getElapsedTime().asSeconds();
	
	if (_fixedDeltaTime > _fixedFrameTime)
		sf::sleep(sf::seconds(_fixedDeltaTime - _fixedFrameTime));

	const auto temp = _fixedTimeClock.getElapsedTime().asSeconds();
	_fixedFrameTime += temp;
	_fixedTime += temp;

	_fixedTimeClock.restart();
}

void GameTime::Manipulate(const float times) {
	_fixedDeltaTime *= times;
}
