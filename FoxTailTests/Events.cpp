#include "stdafx.h"
#include <boost/test/included/unit_test.hpp>
#include <boost/thread/thread.hpp>
#include "FoxTail.hpp"

namespace utf = boost::unit_test;

BOOST_AUTO_TEST_CASE(handlerShouldBeAdded)
{
	int val{ 0 };
	FoxTail::Events::EventBus eb;
	auto e = eb.GetEvent<FoxTail::Events::Event<int>>();
	auto handler = [&val](const int & arg) { val = arg; };
	auto token = e(handler);
	e(42);
	BOOST_TEST(val == 42);
}

BOOST_AUTO_TEST_CASE(handlerShouldBeRemoved)
{
	int val{ 0 };
	FoxTail::Events::EventBus eb;
	auto e = eb.GetEvent<FoxTail::Events::Event<int>>();
	auto handler = [&val](const int & arg) { val = arg; };
	auto token = e(handler);
	e(42);
	BOOST_TEST(val == 42);
	e(token);
	e(0);
	BOOST_TEST(val == 42);
}

BOOST_AUTO_TEST_CASE(handlerCanBeAddedMoreThanOnce)
{
	bool done = false;
	FoxTail::Events::EventToken t1, t2;
	boost::thread t([&t1, &t2, &done]() {
		FoxTail::Events::EventBus eb;
		auto e = eb.GetEvent<FoxTail::Events::Event<int>>();
		auto handler = [](const int & arg) { };
		t1 = e(handler);
		t2 = e(handler);
		done = true;
	});
	using namespace std::chrono_literals;
	int i = 0;
	while (i < 100 && !done) {
		std::this_thread::sleep_for(10ms);
		i++;
	}
	if (!done) {
		TerminateThread(t.native_handle(), 0);
		BOOST_FAIL("timeout error");
	}
	else {
		BOOST_TEST(!(t1 == t2));
	}
}

BOOST_AUTO_TEST_CASE(eventShouldCallAllHandlers, * utf::depends_on("handlerCanBeAddedMoreThanOnce"))
{
	int val{ 0 };
	FoxTail::Events::EventBus eb;
	auto e = eb.GetEvent<FoxTail::Events::Event<int>>();
	auto handler = [&val](const int & arg) { val += arg; };
	e(handler);
	e(handler);
	e(10);
	BOOST_TEST(val == 20);
}