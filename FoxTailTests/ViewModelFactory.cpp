#include "pch.h"
#include <vector>
#include "CppUnitTest.h"
#include "FoxTail.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace ft = FoxTail;
namespace fs = FoxTail::Services;
 
class ViewModel : public ft::ViewModelBase
{
};

class VMFTestServiceInterface : public fs::ServiceInterface {};
class VMFTestService : public VMFTestServiceInterface{};

class ViewModelWithServices : public ft::ViewModelBase, public fs::use_services<VMFTestServiceInterface> {
public: 
	std::shared_ptr<VMFTestServiceInterface> GetTestService() {
		return service<VMFTestServiceInterface>();
	}
};

namespace FoxTailTests
{
	TEST_CLASS(ViewModelFactory)
	{
	public:
		/*TEST_METHOD(ShouldReturnPageViewModel)
		{
			auto vm = ft::ViewModelFactory::Instance().GetViewModel<ViewModel>();
			Assert::IsNotNull(vm.get());
		}

		TEST_METHOD(ShouldReturnPageViewModelWithServices)
		{
			ft::App a;
			a.Container().RegisterService<VMFTestServiceInterface>(std::make_shared<VMFTestService>());
			auto vm = ft::ViewModelFactory::Instance().GetViewModel<ViewModelWithServices>();
			Assert::IsNotNull(vm.get());
			Assert::IsNotNull(vm->GetTestService().get());
			Assert::IsNotNull(dynamic_cast<VMFTestService*>(vm->GetTestService().get()));
		}

		TEST_METHOD(ShouldGiveApplicationViewModel)
		{
			auto vm = ft::ViewModelFactory::Instance().GetViewModel<ViewModel, ft::ViewModelLifetime::Application>();
			Assert::IsNotNull(vm.get());
		}

		TEST_METHOD(ShouldGiveSameApplicationViewModel)
		{
			auto vm = ft::ViewModelFactory::Instance().GetViewModel<ViewModel, ft::ViewModelLifetime::Application>();
			Assert::IsNotNull(vm.get());
			auto vm2 = ft::ViewModelFactory::Instance().GetViewModel<ViewModel, ft::ViewModelLifetime::Application>();
			Assert::IsNotNull(vm2.get());
			Assert::IsTrue(vm.get() == vm2.get());
		}

		TEST_METHOD(ShouldGiveApplicationModelWithServices)
		{
			ft::App a;
			a.Container().RegisterService<VMFTestServiceInterface>(std::make_shared<VMFTestService>());
			auto vm = ft::ViewModelFactory::Instance().GetViewModel<ViewModelWithServices>();
			Assert::IsNotNull(vm.get());
			Assert::IsNotNull(vm->GetTestService().get());
			Assert::IsNotNull(dynamic_cast<VMFTestService*>(vm->GetTestService().get()));
		}*/
	};
}