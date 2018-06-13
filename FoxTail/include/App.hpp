#pragma once
#include "Container.hpp"
#include "Events/EventBus.hpp"

namespace FoxTail {
	class App {
	public:
		App();
		const FoxTail::Container & Container() { return container; }
		const FoxTail::Events::EventBus & EventBus() { return event_bus; }
	protected:
		FoxTail::Container container;
		FoxTail::Events::EventBus event_bus;

		virtual void BeforeInit() {}
		virtual void AfterInit() {}
		virtual void Init();
	private:
		inline static App * current;
	};
}