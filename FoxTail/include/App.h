#pragma once
#include "App.g.h"

namespace winrt::FoxTail::implementation {
	struct App : AppT<App> {
	public:
		App();
		void BeforeInit() {}
		void AfterInit() {}
		void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const&);
		void OnNavigationFailed(IInspectable const&, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const&);
		Windows::UI::Xaml::Interop::TypeName ShellPage();
	private:
	};
}

namespace winrt::FoxTail::factory_implementation {
	struct App : AppT<App, implementation::App>
	{

	};
}