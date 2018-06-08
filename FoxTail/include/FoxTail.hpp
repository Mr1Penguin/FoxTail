#pragma once

#ifdef FOXTAIL_EXPORTS
#define FOXEXPORT __declspec(dllexport)
#else
#define FOXEXPORT __declspec(dllimport)
#endif

#include "Container.hpp"
#include "Services/UseServices.hpp"
#include "Services/ServiceInterface.hpp"