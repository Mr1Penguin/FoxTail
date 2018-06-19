#include "pch.h"
#include "Events/EventToken.hpp"

namespace FoxTail::Events {
	FOXEXPORT bool operator==(const EventToken & left, const EventToken & right) {
		return left.value == right.value;
	}
}