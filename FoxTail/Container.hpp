#pragma once

#include "Services/UseServices.hpp"
#include "Services/ServiceInterface.hpp"

#include <memory>
#include <vector>
#include <type_traits>
#include <algorithm>

namespace FoxTail {
	class Container {
	public:
		template<class TI, class TC>
		void Register(std::shared_ptr<TC> service) {
			static_assert(std::is_base_of_v<TI, TC>);
			static_assert(std::is_base_of_v<Services::ServiceInterface, TI>);
			auto it = std::find_if(services.begin(), services.end(),
				[](std::shared_ptr<Services::ServiceInterface> s) {
				return dynamic_cast<TI*>(s.get()) != nullptr;
			});

			if (it == services.end()) {
				services.push_back(service);
			}
			else {
				*it = service;
			}

			InitService(service.get());
		}

		template <class TI>
		std::shared_ptr<TI> Resolve() {
			auto it = std::find_if(services.begin(), services.end(),
				[](std::shared_ptr<Services::ServiceInterface> s) {
				return dynamic_cast<TI*>(s.get()) != nullptr;
			});

			if (it == services.end())
				throw std::runtime_error("Service not found");

			return std::dynamic_pointer_cast<TI>(*it);
		}
	private:
		std::vector<std::shared_ptr<Services::ServiceInterface>> services;

		template <class... T>
		void InitService(FoxTail::Services::use_services<T...> * s) {
			SetService<T...>(s);
		}

		void InitService(...) {}

		template <class S, class T>
		void SetService(T * s) {
			s->SetService(Resolve<S>());
		}
	};
}