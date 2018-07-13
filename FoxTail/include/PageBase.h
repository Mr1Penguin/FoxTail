#pragma once

#include "ViewModelFactory.h"

namespace FoxTail {
	template <class TViewModel>
	class PageBase {
	public:
		PageBase() {
			m_view_model = ViewModelFactory::Instance().GetViewModel<TViewModel>();
		}

		TViewModel && ViewModel() {
			return std::move(m_view_model);
		}

		virtual ~PageBase() {}
	protected:
		TViewModel m_view_model{ nullptr };
	};
}