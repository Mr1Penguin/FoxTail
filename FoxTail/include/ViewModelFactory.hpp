#pragma once

#include <type_traits>
#include <memory>
#include <vector>
#include "ViewModelBase.hpp"
#include "VectorHelpers.hpp"
#include "Services/UseServices.hpp"

namespace FoxTail {
	enum class ViewModelLifetime {
		Page,
		Application
	};

	class ViewModelFactory {
	public:
		static ViewModelFactory & Instance() {
			static ViewModelFactory instance;
			return instance;
		}

		template<class TViewModel, ViewModelLifetime lifetime = ViewModelLifetime::Page>
		std::shared_ptr<TViewModel> GetViewModel() {
			static_assert(std::is_base_of_v<ViewModelBase, TViewModel>, "TViewModel is not inherited from ViewModelBase");
			static_assert(!std::is_same_v<ViewModelBase, TViewModel>);
			if constexpr (lifetime == ViewModelLifetime::Page) {
				auto tvm = std::make_shared<TViewModel>();
				Services::FillDependencies(tvm.get());
				return std::move(tvm);
			}
			else {
				auto it = find_if_or_push_back(m_application_view_models,
					[](std::shared_ptr<ViewModelBase> & vmb) 
				{ 
					return dynamic_cast<TViewModel*>(vmb.get()) != nullptr; 
				},
					[]()
				{
					auto vm = std::make_shared<TViewModel>();
					Services::FillDependencies(vm.get());
					return std::move(vm);
				});

				return std::dynamic_pointer_cast<TViewModel>(*it);
			}
		}
	private:
		ViewModelFactory()
		{

		}

		std::vector<std::shared_ptr<ViewModelBase>> m_application_view_models;
	};
}