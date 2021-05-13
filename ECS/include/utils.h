// ReSharper disable CppInconsistentNaming
#pragma once

#include <cmath>
#include <functional>
#include <stack>
#include <unordered_set>
#include <vector>
#include <boost/functional/hash.hpp>
#include <SFML/System/Vector2.hpp>

namespace sf::Extensions::Vector2 {
	template <typename T = float>
	constexpr auto Length() {
		return [](const sf::Vector2<T>& vector) -> float {
			return std::sqrt(vector.x * vector.x + vector.y * vector.y);
		};
	}

	template <typename T = float>
	constexpr auto Normalize() {
		return [](const sf::Vector2<T>& vector) -> sf::Vector2<T> {
			return vector * (1 / vector->*Length<T>());
		};
	}

	template <typename T>
	constexpr auto Dot(const sf::Vector2<T>& other) {
		return [&](const sf::Vector2<T>& vector) -> T {
			return vector.x * other.y - vector.y * other.x;
		};
	}

	template <typename T>
	constexpr auto Cross(const sf::Vector2<T>& other) {
		return [&](const sf::Vector2<T>& vector) -> T {
			return vector.x * other.x - vector.y * other.y;
		};
	}

	template <typename T>
	constexpr auto Sin(const sf::Vector2<T>& other) {
		return [&](const sf::Vector2<T>& vector) -> float {
			return vector->*Dot(other) / vector->*Length<T>() / other->*Length<T>();
		};
	}

	template <typename T>
	constexpr auto Cos(const sf::Vector2<T>& other) {
		return [&](const sf::Vector2<T>& vector)-> float {
			return vector->*Cross(other) / vector->*Length<T>() / other->*Length<T>();
		};
	};

	template <typename T = float>
	constexpr auto Normal() {
		return [](const sf::Vector2<T>& vector)-> sf::Vector2<T> {
			return sf::Vector2<T>{vector.y, -vector.x};
		};
	}

	template <typename T>
	constexpr auto SqrMagnitude(const sf::Vector2<T>& other) {
		return [&](const sf::Vector2<T>& vector)-> T {
			return (vector.x - other.x) * (vector.x - other.x) + (vector.y - other.y) * (vector.y - other.y);
		};
	}

	template <typename T>
	constexpr auto Magnitude(const sf::Vector2<T>& other) {
		return [&](const sf::Vector2<T>& vector)-> float {
			return std::sqrt(vector->*SqrMagnitude(other));
		};
	}
} // namespace sf::Extensions::Vector2

template <typename Ext, typename For>
concept ExtensionObj = requires(const For& primary, const Ext& extension) {
	{ extension(primary) };
};

template <typename T, typename E>
	requires ExtensionObj<E, T>
auto operator ->*(T primary, E extension) -> decltype(extension(primary)) {
	return extension(primary);
}
