#pragma once

#include <cstdint>
#include <functional>

namespace FoxTail::Events {
	struct EventToken {
		__int64 value;
		bool operator==(const EventToken & other) const {
			return value == other.value;
		}
	};

	struct EventTokenHash {
		size_t operator() (const EventToken & token) const {
			return std::hash<int64_t>{}(token.value);
		}
	};
}