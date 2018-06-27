#pragma once
#include "Container.hpp"
#include "Events/EventBus.hpp"

namespace FoxTail {
	class App {
	public:
		FOXEXPORT App();
		FoxTail::Container & Container() { return m_container; }
		FoxTail::Events::EventBus & EventBus() { return m_event_bus; }
		static FoxTail::App * Current() { return m_current; }
	protected:
		FoxTail::Container m_container;
		FoxTail::Events::EventBus m_event_bus;

		virtual void BeforeInit() {}
		virtual void AfterInit() {}
		virtual void Init();
	private:
		FOXEXPORT inline static App * m_current = nullptr;
	};
}