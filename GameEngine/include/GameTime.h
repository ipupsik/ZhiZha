#pragma once

#include "SFML/System/Clock.hpp"

class GameTime {
	friend class Engine;

	sf::Clock _timeClock{};
	sf::Clock _fixedTimeClock{};

	double _frameTime = 0;
	float _fixedFrameTime = 0;
	float _fixedDeltaTime = 1 / 25.0f;
	double _deltaTime = 0;
	double _maxDeltaTime = 1 / 60.0f;
	int _frameCount = 0;
	float _fixedTime = 0;
	double _time = 0;

	void waitForUpdate();
	void waitForFixedUpdate();

public:
	GameTime() = default;

	[[nodiscard]] float FixedDeltaTime() const { return _fixedDeltaTime; }
	[[nodiscard]] double DeltaTime() const { return _deltaTime; }
	[[nodiscard]] int FrameCount() const { return _frameCount; }
	[[nodiscard]] float FixedTime() const { return _fixedTime; }
	[[nodiscard]] double Time() const { return _time; }
	
	/// <summary>
	/// Slows down or speeds up time in game
	/// </summary>
	/// <param name="times">The factor to be multiplied with frame time</param>
	void Manipulate(float times);
};
