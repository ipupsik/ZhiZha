#pragma once

template <typename T>
class TypeFamily {
	static std::atomic<std::size_t> _idCount;

public:
	template <std::derived_from<T> U>
	static std::size_t Type() {
		static const std::size_t ID = _idCount++;
		return ID;
	}
};

template <typename T>
std::atomic<std::size_t> TypeFamily<T>::_idCount = std::atomic<std::size_t>(0);
