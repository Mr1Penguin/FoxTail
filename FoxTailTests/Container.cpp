#include "stdafx.h"

#include "../FoxTail/FoxTail.h"

BOOST_AUTO_TEST_SUITE(test_suite1)

struct TestServiceInterface : FoxTail::Services::ServiceInterface {};

struct TestService : TestServiceInterface {};

BOOST_AUTO_TEST_CASE(containerShouldRegisterAndResolveService)
{
	using namespace FoxTail;
	using namespace FoxTail::Services;
	Container c;
	c.Register<TestServiceInterface>(std::make_shared<TestService>());
	auto ts = c.Resolve<TestServiceInterface>();
	BOOST_TEST(ts != nullptr);
}

BOOST_AUTO_TEST_CASE(containerShouldThrowExceptionOnResolvingNonExistingService)
{
	using namespace FoxTail;
	using namespace FoxTail::Services;
	Container c;
	BOOST_CHECK_THROW(c.Resolve<TestServiceInterface>(), std::runtime_error);
}

struct ServiceWithDependenceInterface : FoxTail::Services::ServiceInterface {};

struct ServiceWithDependence : ServiceWithDependenceInterface, FoxTail::Services::use_services<TestServiceInterface>
{
	auto TestService() { return this->service<TestServiceInterface>(); }
};

BOOST_AUTO_TEST_SUITE(test_suite2)

BOOST_AUTO_TEST_CASE(containerShouldRegisterServiceWithDependences)
{
	using namespace FoxTail;
	using namespace FoxTail::Services;
	Container c;
	c.Register<TestServiceInterface>(std::make_shared<TestService>());
	c.Register<ServiceWithDependenceInterface>(std::make_shared<ServiceWithDependence>());
	auto ts = std::dynamic_pointer_cast<ServiceWithDependence>(c.Resolve<ServiceWithDependenceInterface>());
	BOOST_TEST(ts != nullptr);
	BOOST_TEST(ts->TestService() != nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()