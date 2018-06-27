#pragma once

#include <cstdint>
#include <functional>
#include "export.h"

namespace FoxTail::Events {
	struct EventToken {
		__int64 value;
	};

	struct EventTokenHash {
		size_t operator() (const EventToken & token) const {
			return std::hash<int64_t>{}(token.value);
		}
	};

	FOXEXPORT bool operator==(const EventToken & left, const EventToken & right);
}