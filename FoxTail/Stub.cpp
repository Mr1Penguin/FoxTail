#include "pch.h"
#include "Stub.h"

using namespace winrt;

namespace winrt::FoxTail::implementation
{
    int32_t Stub::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void Stub::MyProperty(int32_t /*value*/)
    {
        throw hresult_not_implemented();
    }
}
