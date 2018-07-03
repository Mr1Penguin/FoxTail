#include "pch.h"
#include "App.h"

using namespace winrt;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace FoxTail::implementation;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;

App::App()
{
}

void App::OnLaunched(LaunchActivatedEventArgs const& e)
{
	Frame rootFrame{ nullptr };
	auto content = Window::Current().Content();
	if (content)
	{
		rootFrame = content.try_as<Frame>();
	}

	// Do not repeat app initialization when the Window already has content,
	// just ensure that the window is active
	if (rootFrame == nullptr)
	{
		// Create a Frame to act as the navigation context and associate it with
		// a SuspensionManager key
		rootFrame = FoxTail::Frame();

		rootFrame.NavigationFailed({ this, &App::OnNavigationFailed });

		if (e.PreviousExecutionState() == ApplicationExecutionState::Terminated)
		{
			// Restore the saved session state only when appropriate, scheduling the
			// final launch steps after the restore is complete
		}

		if (e.PrelaunchActivated() == false)
		{
			if (rootFrame.Content() == nullptr)
			{
				// When the navigation stack isn't restored navigate to the first page,
				// configuring the new page by passing required information as a navigation
				// parameter
				rootFrame.Navigate(ShellPage(), box_value(e.Arguments()));
			}
			// Place the frame in the current Window
			Window::Current().Content(rootFrame);
			// Ensure the current window is active
			Window::Current().Activate();
		}
	}
	else
	{
		if (e.PrelaunchActivated() == false)
		{
			if (rootFrame.Content() == nullptr)
			{
				// When the navigation stack isn't restored navigate to the first page,
				// configuring the new page by passing required information as a navigation
				// parameter
				rootFrame.Navigate(ShellPage(), box_value(e.Arguments()));
			}
			// Ensure the current window is active
			Window::Current().Activate();
		}
	}
}

/// <summary>
/// Invoked when Navigation to a certain page fails
/// </summary>
/// <param name="sender">The Frame which failed navigation</param>
/// <param name="e">Details about the navigation failure</param>
void App::OnNavigationFailed(IInspectable const&, NavigationFailedEventArgs const& e)
{
	throw hresult_error(E_FAIL, hstring(L"Failed to load Page ") + e.SourcePageType().Name);
}

Windows::UI::Xaml::Interop::TypeName App::ShellPage() 
{
	throw hresult_error(E_FAIL, hstring(L"ShellPage factory method is not overridden"));
}