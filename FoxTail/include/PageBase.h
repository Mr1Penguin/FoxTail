#pragma once

#include "ViewModelFactory.h"

namespace FoxTail {
	template <class TViewModel>
	class PageBase {
	public:
		PageBase() {
			m_view_model = ViewModelFactory::Instance().GetViewModel<TViewModel>();
		}

		TViewModel & ViewModel() {
			return *m_view_model;
		}

		virtual ~PageBase() {}
	protected:
		winrt::com_ptr<TViewModel> m_view_model{ nullptr };
	};
}