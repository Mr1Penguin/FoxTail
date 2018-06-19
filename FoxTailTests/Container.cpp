#include "pch.h"
#include "CppUnitTest.h"
#include "FoxTail.hpp"

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
			ft::Container c;
			c.RegisterService<TestServiceInterface>(std::make_shared<TestService>());
			auto ts = c.ResolveService<TestServiceInterface>();
			Assert::IsNotNull(ts.get());
        }

		TEST_METHOD(ShouldThrowExceptionOnResolvingNonExistingService)
		{
			ft::Container c;
			Assert::ExpectException<std::runtime_error>([&c] { c.ResolveService<TestServiceInterface>(); });
		}

		TEST_METHOD(ShouldRegisterServiceWithDependences)
		{
			ft::Container c;
			c.RegisterService<TestServiceInterface>(std::make_shared<TestService>());
			c.RegisterService<ServiceWithDependenceInterface>(std::make_shared<ServiceWithDependence>());
			auto ts = std::dynamic_pointer_cast<ServiceWithDependence>(c.ResolveService<ServiceWithDependenceInterface>());
			Assert::IsNotNull(ts.get());
			Assert::IsNotNull(ts->TestService().get());
		}
    };
}