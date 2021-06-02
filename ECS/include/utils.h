// ReSharper disable CppInconsistentNaming
#pragma once

#include <cmath>
#include <SFML/System/Vector2.hpp>

#if defined(linux)
constexpr auto PI = M_PI;
#else
constexpr auto PI = 3.14159265358979323846;
#endif

template <typename Ext, typename For>
concept ExtensionObj = requires(const For& primary, const Ext& extension) {
	{ extension(primary) };
};

template <typename T, typename E>
requires ExtensionObj<E, T>
constexpr auto operator->*(T primary, E extension) -> decltype(extension(primary)) {
	return extension(primary);
}

namespace sf::Extensions::Vector2 {
	template <typename T = float>
	constexpr auto Length() {
		return [](const sf::Vector2<T>& vector) constexpr -> float {
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
		return [&](const sf::Vector2<T>& vector) constexpr -> T {
			return vector.x * other.x - vector.y * other.y;
		};
	}

	template <typename T>
	constexpr auto Cross(const sf::Vector2<T>& other) {
		return [&](const sf::Vector2<T>& vector) constexpr -> T {
			return vector.x * other.y - vector.y * other.x;
		};
	}

	template <typename T>
	constexpr auto Sin(const sf::Vector2<T>& other) {
		return [&](const sf::Vector2<T>& vector) constexpr -> float {
			return vector->*Cross(other) / vector->*Length<T>() / other->*Length<T>();
		};
	}

	template <typename T>
	constexpr auto Cos(const sf::Vector2<T>& other) {
		return [&](const sf::Vector2<T>& vector) constexpr -> float {
			return vector->*Dot(other) / vector->*Length<T>() / other->*Length<T>();
		};
	};

	template <typename T = float>
	constexpr auto Normal() {
		return [](const sf::Vector2<T>& vector) -> sf::Vector2<T> {
			return sf::Vector2<T>{ vector.y, -vector.x };
		};
	}

	template <typename T>
	constexpr auto SqrMagnitude(const sf::Vector2<T>& other) {
		return [&](const sf::Vector2<T>& vector) constexpr -> T {
			return (vector.x - other.x) * (vector.x - other.x)
					+ (vector.y - other.y) * (vector.y - other.y);
		};
	}

	template <typename T>
	constexpr auto Magnitude(const sf::Vector2<T>& other) {
		return [&](const sf::Vector2<T>& vector) constexpr -> float {
			return std::sqrt(vector->*SqrMagnitude(other));
		};
	}

	template <typename T = float>
	constexpr auto RotateRad(const double radians) {
		return [radians](const sf::Vector2<T>& vector) {
			return sf::Vector2f{
					static_cast<float>(std::cos(radians) * vector.x - std::sin(radians) * vector.y),
					static_cast<float>(std::sin(radians) * vector.x + std::cos(radians) * vector.y)
			};
		};
	}

	template <typename T = float>
	constexpr auto RotateDeg(const double degrees) {
		return RotateRad<T>(PI * degrees / 180.0);
	}
} // namespace sf::Extensions::Vector2

template <typename F, std::size_t ...Index>
constexpr void foreach(F f, std::integer_sequence<const std::size_t, Index...>) {
	auto res = { (f(std::integral_constant<const std::size_t, Index>()), 0)... };
}