#pragma once

#include <type_traits>
#include <memory>
#include <vector>
#include "VectorHelpers.h"
#include "Services/UseServices.h"

namespace FoxTail {
	
	using ViewModelBase = winrt::FoxTail::ViewModelBase;

	class ViewModelFactory {
	public:
		static ViewModelFactory & Instance() {
			static ViewModelFactory instance;
			return instance;
		}

		template<class TViewModel>
		void RegisterApplicationViewModel() {
			//static_assert(std::is_base_of_v<winrt::impl::base_one<TViewModel, ViewModelBase>, TViewModel>, "TViewModel is not inherited from ViewModelBase");
			static_assert(!std::is_same_v<ViewModelBase, TViewModel>);
			replace_or_push_back(m_application_view_models, 
				[](auto & vmb)
			{
				return vmb.try_as<TViewModel>() != nullptr;
			},
				[&]() 
			{
				TViewModel vm;
				//Services::FillDependencies(vm);
				return std::move(vm);
			});
		}

		template<class TViewModel>
		TViewModel GetViewModel() {
			static_assert(std::is_base_of_v<winrt::impl::base_one<TViewModel,ViewModelBase>, TViewModel>, "TViewModel is not inherited from ViewModelBase");
			static_assert(!std::is_same_v<ViewModelBase, TViewModel>);
			auto it = std::find_if(std::begin(m_application_view_models), std::end(m_application_view_models),
				[](auto & vmb)
			{
				return vmb.try_as<TViewModel>() != nullptr;
			});
			if (it == std::end(m_application_view_models)) {
				//auto vm = winrt::make_self<TViewModel>();
				TViewModel vm;
				//Services::FillDependencies(*vm);
				return std::move(vm);
			}
			return nullptr;
			//return it->try_as<TViewModel>();
		}
	private:
		ViewModelFactory()
		{
		}

		ViewModelFactory(const ViewModelFactory &) = delete;
		void operator=(const ViewModelFactory &) = delete;

		std::vector<ViewModelBase> m_application_view_models;
	};
}