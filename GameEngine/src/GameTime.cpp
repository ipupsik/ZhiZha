#include "GameTime.h"

#include "SFML/System/Sleep.hpp"

void GameTime::waitForUpdate() {
	_frameCount++;
	
	const auto temp = _timeClock.restart().asSeconds();
	_frameTime += temp;
	_time += temp;
	_deltaTime = temp;

	if (_maxDeltaTime > _frameTime)
		sf::sleep(sf::seconds(_maxDeltaTime - _frameTime));
	_frameTime = 0;
}

void GameTime::waitForFixedUpdate() {
	const auto temp = _fixedTimeClock.restart().asSeconds();
	_fixedFrameTime += temp;
	_fixedTime += temp;
	
	if (_fixedDeltaTime > _fixedFrameTime)
		sf::sleep(sf::seconds(_fixedDeltaTime - _fixedFrameTime));
	_fixedFrameTime = 0;
}

void GameTime::Manipulate(const float times) {
	_fixedDeltaTime *= times;
}
