#pragma once

#include "ViewModelBase.g.h"

namespace winrt::FoxTail::implementation {

	class ViewModelBase : public ViewModelBaseT<ViewModelBase> {
	public:
		void PropertyChanged(winrt::event_token token) {
			m_property_changed.remove(token);
		}

		winrt::event_token PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const & handler) {
			return m_property_changed.add(handler);
		}

		virtual ~ViewModelBase() {}

	protected:
		template<class T>
		void SetProperty(T & prop, T & new_val, winrt::hstring prop_name) {
			if (prop == new_val) return;
			prop = new_val;
			m_property_changed(*this, winrt::Windows::UI::Xaml::Data::PropertyChangedEventArgs(prop_name));
		}

		template<class T, class H>
		void SetProperty(T & prop, T & new_val, winrt::hstring prop_name, H handler) {
			if (prop == new_val) return;
			prop = new_val;
			m_property_changed(*this, winrt::Windows::UI::Xaml::Data::PropertyChangedEventArgs(prop_name));
			H(prop);
		}

	private:
		winrt::event<winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler> m_property_changed;
	};
}

namespace FoxTail {
}

namespace winrt::FoxTail::factory_implementation {

	struct ViewModelBase : ViewModelBaseT<ViewModelBase, implementation::ViewModelBase>
	{

	};
}