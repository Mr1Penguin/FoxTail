#pragma once

#include <type_traits>
#include "Event.hpp"

namespace FoxTail::Events {
	class EventBus {
	public:
		template<class TEvent>
		const TEvent & GetEvent() {
			static_assert(std::is_base_of_v<detail::Event, TEvent>, "TEvent is not inherited from Event<TPayload>");
			static TEvent instance;
			return instance;
		}
	};
}