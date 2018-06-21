#pragma once

#include <type_traits>
#include <vector>
#include <memory>
#include <nanorange.hpp>
#include "Event.hpp"

namespace FoxTail::Events {
	class EventBus {
	public:
		template<class TEvent>
		TEvent & GetEvent() {
			static_assert(std::is_base_of_v<detail::Event, TEvent>, "TEvent is not inherited from Event<TPayload>");
			auto it = nano::find_if(events, [](std::shared_ptr<detail::Event> & e) { return std::dynamic_pointer_cast<TEvent>(e) != nullptr; });
			/*auto e = new TEvent;
			auto gg = std::shared_ptr<TEvent>(e);*/
			return *std::dynamic_pointer_cast<TEvent>(it == std::end(events) ? events.emplace_back(std::make_shared<TEvent>()) : *it);
		}

	private:
		std::vector<std::shared_ptr<detail::Event>> events;
	};
}