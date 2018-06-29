#pragma once

#include "Frame.g.h"

namespace winrt::FoxTail::implementation {
	//Frame for content inside shell
	class Frame : public FrameT<Frame> {
	};
}

namespace winrt::FoxTail::factory_implementation {
	struct Frame : FrameT<Frame, implementation::Frame> {

	};
}