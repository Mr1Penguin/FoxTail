#include "pch.h"
#include "CppUnitTest.h"
#include "FoxTail.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace ft = FoxTail;
namespace fs = FoxTail::Services;
namespace fe = FoxTail::Events;

struct TestEvent : fe::Event<int> {};

namespace FoxTailTests
{
	TEST_CLASS(Event)
	{
	public:
		TEST_METHOD(HandlerShouldBeAdded)
		{
			int val{ 0 };
			fe::EventBus eb;
			auto & e = eb.GetEvent<TestEvent>();
			auto handler = [&val](const int & arg) { val = arg; };
			auto token = e(handler);
			e(42);
			Assert::AreEqual(42, val);
		}

		TEST_METHOD(HandlerShouldBeRemoved)
		{
			int val{ 0 };
			fe::EventBus eb;
			auto & e = eb.GetEvent<TestEvent>();
			auto handler = [&val](const int & arg) { val = arg; };
			auto token = e(handler);
			e(token);
			e(1);
			Assert::AreNotEqual(1, val);
		}

		TEST_METHOD(HandlerCanBeAddedMoreThanOnce)
		{
			fe::EventToken t1, t2;
			fe::EventBus eb;
			auto & e = eb.GetEvent<TestEvent>();
			auto handler = [](const int & arg) {};
			t1 = e(handler);
			t2 = e(handler);
			Assert::IsTrue(!(t1 == t2));
		}

		TEST_METHOD(ShouldCallAllHandlers)
		{
			int val{ 0 };
			fe::EventBus eb;
			auto & e = eb.GetEvent<TestEvent>();
			auto handler = [&val](const int & arg) { val += arg; };
			e(handler);
			e(handler);
			e(10);
			Assert::AreEqual(20, val);
		}

		TEST_METHOD(ShouldGiveSameEvent) 
		{
			fe::EventBus eb;
			auto & e1 = eb.GetEvent<TestEvent>();
			auto & e2 = eb.GetEvent<TestEvent>();
			Assert::IsTrue(&e1 == &e2);
		}
	};
}