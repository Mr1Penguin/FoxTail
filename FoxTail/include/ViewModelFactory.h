#pragma once

#include <type_traits>
#include <memory>
#include <vector>
#include "ViewModelBase.h"
#include "VectorHelpers.h"
#include "Services/UseServices.h"

namespace FoxTail {
	
	class ViewModelFactory {
	public:
		static ViewModelFactory & Instance() {
			static ViewModelFactory instance;
			return instance;
		}

		template<class TViewModel, class... TArgs>
		void RegisterApplicationViewModel(TArgs... args) {
			static_assert(std::is_base_of_v<ViewModelBase, TViewModel>, "TViewModel is not inherited from ViewModelBase");
			static_assert(!std::is_same_v<ViewModelBase, TViewModel>);
			replace_or_push_back(m_application_view_models, 
				[](std::shared_ptr<ViewModelBase> & vmb)
			{
				return dynamic_cast<TViewModel*>(vmb.get()) != nullptr;
			},
				[&]() 
			{
				auto vm = std::make_shared<TViewModel>(args...);
				Services::FillDependencies(vm.get());
				return std::move(vm);
			});
		}

		template<class TViewModel>
		std::shared_ptr<TViewModel> GetViewModel() {
			static_assert(std::is_base_of_v<ViewModelBase, TViewModel>, "TViewModel is not inherited from ViewModelBase");
			static_assert(!std::is_same_v<ViewModelBase, TViewModel>);
			auto it = nano::find_if(m_application_view_models,
				[](std::shared_ptr<ViewModelBase> & vmb)
			{
				return dynamic_cast<TViewModel*>(vmb.get()) != nullptr;
			});
			if (it == nano::end(m_application_view_models)) {
				auto tvm = std::make_shared<TViewModel>();
				Services::FillDependencies(tvm.get());
				return std::move(tvm);
			}

			return *it;
		}
	private:
		ViewModelFactory()
		{
		}

		ViewModelFactory(const ViewModelFactory &) = delete;
		void operator=(const ViewModelFactory &) = delete;

		std::vector<std::shared_ptr<ViewModelBase>> m_application_view_models;
	};
}