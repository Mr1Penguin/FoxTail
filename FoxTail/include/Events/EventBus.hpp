#pragma once

#include <type_traits>
#include <vector>
#include <memory>
#include <nanorange.hpp>
#include "Event.hpp"

namespace FoxTail::Events {

	namespace detail {
		template <class T>
		struct is_event : std::false_type {};

		template <class T>
		struct is_event<FoxTail::Events::Event<T>> : std::true_type {};

		template <class T>
		constexpr bool is_event_v = is_event<T>::value;
	}


	class EventBus {
	public:
		template<class TEvent>
		TEvent & GetEvent() {
			static_assert(std::is_base_of_v<detail::Event, TEvent>, "TEvent is not inherited from Event<TPayload>");
			static_assert(!detail::is_event_v<TEvent>, "TEvent cannot be Event<TPayload>");
			auto it = nano::find_if(events, [](std::shared_ptr<detail::Event> & e) { return std::dynamic_pointer_cast<TEvent>(e) != nullptr; });
			
			return *std::dynamic_pointer_cast<TEvent>(it == std::end(events) ? events.emplace_back(std::make_shared<TEvent>()) : *it);
		}

	private:
		std::vector<std::shared_ptr<detail::Event>> events;
	};
}