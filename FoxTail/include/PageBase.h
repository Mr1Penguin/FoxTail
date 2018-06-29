#pragma once

namespace FoxTail {
	template <class TViewModel>
	class PageBase {
	public:
		PageBase() {
			m_view_model = ViewModelFactory.Instance().GetViewModel<TViewModel>();
		}

		TViewModel & ViewModel() {
			return *m_view_model;
		}

		virtual ~PageBase() {}
	protected:
		std::shared_ptr<TViewModel> m_view_model;
	};
}