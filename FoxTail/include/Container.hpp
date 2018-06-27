#pragma once

#include <memory>
#include <vector>
#include <type_traits>
#include <algorithm>
#include <nanorange.hpp>

#include "Services/ServiceInterface.hpp"
#include "Services/UseServices.hpp"
#include "VectorHelpers.hpp"

namespace FoxTail {
	class Container {
	public:
		template<class TI, class TC>
		void RegisterService(std::shared_ptr<TC> service) {
			static_assert(std::is_base_of_v<TI, TC>);
			static_assert(std::is_base_of_v<Services::ServiceInterface, TI>);
			replace_or_push_back(m_services,
				[](std::shared_ptr<Services::ServiceInterface> & s) { return dynamic_cast<TI*>(s.get()) != nullptr; },
				[&service](){return service;});

			FillDependencies(service.get());
		}

		template <class TI>
		std::shared_ptr<TI> ResolveService() const {
			static_assert(std::is_base_of_v<Services::ServiceInterface, TI>);
			auto it = nano::find_if(m_services,
				[](std::shared_ptr<Services::ServiceInterface> s) {
				return dynamic_cast<TI*>(s.get()) != nullptr;
			});

			if (it == nano::end(m_services))
				throw std::runtime_error("Service not found"); //maybe return nullptr or replace with custom exception

			return std::dynamic_pointer_cast<TI>(*it);
		}

	private:
		std::vector<std::shared_ptr<Services::ServiceInterface>> m_services;
	};
}