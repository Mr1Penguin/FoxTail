#include "pch.h"
#include "CppUnitTest.h"
#include "FoxTail.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace ft = FoxTail;
namespace fs = FoxTail::Services;

struct TestServiceInterface : fs::ServiceInterface {};

struct TestService : TestServiceInterface {};

struct ServiceWithDependenceInterface : FoxTail::Services::ServiceInterface {};

struct ServiceWithDependence : ServiceWithDependenceInterface, fs::use_services<TestServiceInterface>
{
	auto TestService() { return this->service<TestServiceInterface>(); }
};

namespace FoxTailTests
{
    TEST_CLASS(Container)
    {
    public:
        TEST_METHOD(ShouldRegisterAndResolveService)
        {
			ft::App app;
			app.Container().RegisterService<TestServiceInterface>(std::make_shared<TestService>());
			auto ts = app.Container().ResolveService<TestServiceInterface>();
			Assert::IsNotNull(ts.get());
        }

		TEST_METHOD(ShouldThrowExceptionOnResolvingNonExistingService)
		{
			ft::App app;
			Assert::ExpectException<std::runtime_error>([&app] { app.Container().ResolveService<TestServiceInterface>(); });
		}

		TEST_METHOD(ShouldRegisterServiceWithDependences)
		{
			ft::App app;
			app.Container().RegisterService<TestServiceInterface>(std::make_shared<TestService>());
			app.Container().RegisterService<ServiceWithDependenceInterface>(std::make_shared<ServiceWithDependence>());
			auto ts = std::dynamic_pointer_cast<ServiceWithDependence>(app.Container().ResolveService<ServiceWithDependenceInterface>());
			Assert::IsNotNull(ts.get());
			Assert::IsNotNull(ts->TestService().get());
		}
    };
}