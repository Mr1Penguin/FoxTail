#pragma once

#include <memory>

namespace FoxTail::Services {
	template <class Service>
	struct ServiceUser {
		void SetService(std::shared_ptr<Service> service) {
			this->service = service;
		}
	protected:
		std::shared_ptr<Service> service;
	};

	template<class Service>
	struct get_service_user {
		typedef ServiceUser<Service> type;
	};

	template<class... Services>
	struct use_services : get_service_user<Services...>::type
	{
	protected:
		template<class TService>
		std::shared_ptr<TService> service() {
			return ServiceUser<TService>::service;
		}
	};
}