#pragma once

#include <unordered_map>
#include <delegate.hpp>
#include <random>
#include <algorithm>
#include "EventToken.hpp"

namespace FoxTail::Events {
	namespace detail {
		class Event {
		public:
			virtual ~Event() {}
		};

		template<class TDelegate>
		class EventBase : public Event {
		public:
			EventBase<TDelegate>() = default;
			EventBase<TDelegate>(EventBase<TDelegate> const &) = delete;
			void operator=(EventBase<TDelegate> const &) = delete;
			virtual ~EventBase<TDelegate>() {}
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
	}

	template<class TPayload>
	class Event : public detail::EventBase<delegate<void(const TPayload &)>> {
		typedef detail::EventBase<delegate<void(const TPayload &)>> base;
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

		~Event<TPayload>() {}
	};

	template<>
	class Event<void> : public detail::EventBase<delegate<void()>> {
		typedef detail::EventBase<delegate<void()>> base;
	public:
		EventToken operator()(delegate<void()> handler) {
			return base::AddHandler(handler);
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

		~Event<void>() {}
	};
}
