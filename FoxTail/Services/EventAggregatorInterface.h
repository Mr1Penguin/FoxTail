#pragma once

#include "ServiceInterface.h"

namespace FoxTail::Services {
	struct EventAggregatorInterface : ServiceInterface {
		virtual void Subscribe() = 0;
		virtual void Publish() = 0;

		virtual ~EventAggregatorInterface() {};
	};
}