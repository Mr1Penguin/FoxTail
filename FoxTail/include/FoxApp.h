#pragma once
#include "FoxApp.g.h"

namespace winrt::FoxTail::implementation {
	struct FoxApp : FoxAppT<FoxApp> {
	public:
		FoxApp();
		void BeforeInit() {}
		void AfterInit() {}
		void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const&);
		void OnNavigationFailed(IInspectable const&, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const&);
		int32_t Life() { return life; }
		Windows::UI::Xaml::Interop::TypeName ShellPage();
	private:
		int32_t life;
	};
}

namespace winrt::FoxTail::factory_implementation {
	struct FoxApp : FoxAppT<FoxApp, implementation::FoxApp>
	{
		//void CreateInstance(Windows::Foundation::IInspectable const& baseInterface, Windows::Foundation::IInspectable& innerInterface){

		//}
	};
}