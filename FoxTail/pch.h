//
// pch.h
// Header for platform projection include files
//

#pragma once

#define NOMINMAX
#pragma comment(lib, "Ole32.lib") 
#include "Windows.h"
#include <unknwn.h>
#include "winrt/Windows.Foundation.h"
#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Data.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Navigation.h"
#include "winrt/Windows.ApplicationModel.Activation.h"

#include <nanorange.hpp>
#include <unordered_map>
#include <delegate.hpp>
#include <random>
#include <algorithm>
#include <type_traits>
#include <vector>
#include <cstdint>
#include <functional>



#define PERMISSIVEFIX //remove if code compile ok with /permissive-