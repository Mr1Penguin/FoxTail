#pragma once

#include <unordered_map>
#include <delegate.hpp>
#include <random>
#include <algorithm>
#include "EventToken.hpp"

namespace FoxTail::Events {
	namespace detail {
		struct Event {

		};
	}

	template<class TDelegate>
	class BaseEvent : public detail::Event {
	protected:
		EventToken AddHandler(TDelegate & handler) {
			static std::mt19937_64 rng{ std::random_device{}() };
			EventToken token;
			do {
				token.value = rng();
			} while (handlers.find(token) != handlers.end());

			handlers.insert({ token, handler });
			return token;
		}

		void RemoveHandler(EventToken token) {
			handlers.erase(token);
		}

		std::unordered_map<EventToken, TDelegate, EventTokenHash> handlers;
	};

	template<class TPayload>
	class Event : public BaseEvent<delegate<void(const TPayload &)>> {
		typedef BaseEvent<delegate<void(const TPayload &)>> base;
	public:
		EventToken operator()(delegate<void(const TPayload &)> handler) {
			return base::AddHandler(handler);
		}

		void operator()(EventToken token) {
			base::RemoveHandler(token);
		}

		void operator()(const TPayload & payload) {
			std::for_each(std::begin(base::handlers), std::end(base::handlers),
				[payload](auto p) {
				p.second(payload);
			});
		}
	};

	template<>
	class Event<void> : public BaseEvent<delegate<void()>> {
		typedef BaseEvent<delegate<void()>> base;
	public:
		EventToken operator()(delegate<void()> handler) {
			return AddHandler(handler);
		}

		void operator()(EventToken token) {
			base::RemoveHandler(token);
		}

		void operator()() {
			std::for_each(std::begin(base::handlers), std::end(base::handlers),
				[](auto p) {
				p.second();
			});
		}	
	};
}	