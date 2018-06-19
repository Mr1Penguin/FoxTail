//
// Declaration of the Stub class.
//

#pragma once

#include "Stub.g.h"

namespace winrt::FoxTail::implementation
{
    struct Stub : StubT<Stub>
    {
        Stub() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::FoxTail::factory_implementation
{
    struct Stub : StubT<Stub, implementation::Stub>
    {
    };
}
