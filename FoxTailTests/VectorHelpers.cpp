#include "pch.h"
#include <vector>
#include "CppUnitTest.h"
#include "FoxTail.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace ft = FoxTail;

namespace FoxTailTests
{
	TEST_CLASS(VectorHelpers)
	{
	public:
		TEST_METHOD(ReplaceOrPushBackShouldPushNew)
		{
			std::vector<int> ints{ 1,2,3 };
			ft::replace_or_push_back(ints, [](int & v) { return v == 5; }, []() {return 5; });
			Assert::AreEqual(size_t{ 4 }, ints.size());
			Assert::AreEqual(5, ints.back());
		}

		TEST_METHOD(ReplaceOrPushBackShouldReplaceExisting)
		{
			std::vector<int> ints{ 1,2,3 };
			ft::replace_or_push_back(ints, [](int & v) { return v == 3; }, []() {return 5; });
			Assert::AreEqual(size_t{ 3 }, ints.size());
			Assert::AreEqual(5, ints[2]);
		}

		TEST_METHOD(FindIfOrPushBackShouldReturnExisting)
		{
			std::vector<int> ints{ 1,2,3,4 };
			auto it = ft::find_if_or_push_back(ints, [](int & v) { return v == 3; }, []() {return 5; });
			Assert::AreEqual(size_t{ 4 }, ints.size());
			Assert::AreEqual(3, *it);
		}

		TEST_METHOD(BugCatcher) {}

		TEST_METHOD(FindIfOrPushBackShouldPushNew)
		{
			std::vector<int> ints{ 1,2,3,4 };
			auto it = ft::find_if_or_push_back(ints, [](int & v) { return v == 5; }, []() {return 10; });
			Assert::AreEqual(size_t{ 5 }, ints.size());
			Assert::IsTrue(ints.end() - 1 == it);
			Assert::AreEqual(10, *it);
		}
	};
}