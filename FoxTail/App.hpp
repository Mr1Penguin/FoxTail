#pragma once
#include "Container.hpp"

namespace FoxTail {
	class App {
	public:
		const FoxTail::Container & Container() { return container; }
	protected:
		FoxTail::Container container;

		virtual void BeforeInit() {}
		virtual void AfterInit() {}
		virtual void Init();
	};
}