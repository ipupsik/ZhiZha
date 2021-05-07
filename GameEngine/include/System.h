#pragma once

#include <string>

#include "TypeFamily.h"

class SystemBase {
protected:
	virtual void onUpdate() {}
	
	virtual void onFixedUpdate() {}

public:
	virtual ~SystemBase() = default;
};

template <typename T>
struct System: public SystemBase {
	static std::size_t Type;
};

template <typename T>
std::size_t System<T>::Type = TypeFamily<SystemBase>::Type<T>();
