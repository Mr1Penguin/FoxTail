#pragma once

#ifdef FOXTAIL_EXPORTS
#define FOXEXPORT __declspec(dllexport)
#else
#define FOXEXPORT __declspec(dllimport)
#endif