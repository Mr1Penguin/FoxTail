#pragma once

#include "Container.h"
#include "Events/EventBus.h"

namespace FoxTail {
	class App2 {
	public:
		App2() {
			m_current = this;
		}
		::FoxTail::Container & Container() { return m_container; }
		::FoxTail::Events::EventBus & EventBus() { return m_event_bus; }
		static ::FoxTail::App2 * Current() { return m_current; }
	protected:
		::FoxTail::Container m_container;
		::FoxTail::Events::EventBus m_event_bus;
	private:
		inline static App2 * m_current { nullptr };
	};
}