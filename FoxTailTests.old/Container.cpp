#include "stdafx.h"

#define BOOST_TEST_MODULE FoxTail
#include <boost/test/unit_test.hpp>
#include "FoxTail.hpp"

struct TestServiceInterface : FoxTail::Services::ServiceInterface {};

struct TestService : TestServiceInterface {};

BOOST_AUTO_TEST_CASE(containerShouldRegisterAndResolveService)
{
	using namespace FoxTail;
	using namespace FoxTail::Services;
	Container c;
	c.RegisterService<TestServiceInterface>(std::make_shared<TestService>());
	auto ts = c.ResolveService<TestServiceInterface>();
	BOOST_TEST(ts != nullptr);
}

BOOST_AUTO_TEST_CASE(containerShouldThrowExceptionOnResolvingNonExistingService)
{
	using namespace FoxTail;
	using namespace FoxTail::Services;
	Container c;
	BOOST_CHECK_THROW(c.ResolveService<TestServiceInterface>(), std::runtime_error);
}

struct ServiceWithDependenceInterface : FoxTail::Services::ServiceInterface {};

struct ServiceWithDependence : ServiceWithDependenceInterface, FoxTail::Services::use_services<TestServiceInterface>
{
	auto TestService() { return this->service<TestServiceInterface>(); }
};

BOOST_AUTO_TEST_CASE(containerShouldRegisterServiceWithDependences)
{
	using namespace FoxTail;
	using namespace FoxTail::Services;
	Container c;
	c.RegisterService<TestServiceInterface>(std::make_shared<TestService>());
	c.RegisterService<ServiceWithDependenceInterface>(std::make_shared<ServiceWithDependence>());
	auto ts = std::dynamic_pointer_cast<ServiceWithDependence>(c.ResolveService<ServiceWithDependenceInterface>());
	BOOST_TEST(ts != nullptr);
	BOOST_TEST(ts->TestService() != nullptr);
}