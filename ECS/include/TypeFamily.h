#pragma once

#include <atomic>

class TypeFamily {
	static std::atomic_size_t _idCount;

public:
	template<typename U>
	static std::size_t Type() {
		static const std::size_t ID = _idCount++;
		return ID;
	}
};

std::atomic_size_t TypeFamily::_idCount{ 0 };
