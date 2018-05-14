#pragma once

#ifdef FOXTAIL_EXPORTS
#define FOXEXPORT __declspec(dllexport)
#else
#define FOXEXPORT __declspec(dllimport)
#endif

#include "Container.h"
#include "Services/UseServices.h"
#include "Services/ServiceInterface.h"