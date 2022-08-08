#pragma once

// attempt to detect MSVC in case cmake did not.
// intel compiler defines _MSC_VER and also __INTEL_COMPILER.
#if !defined(MSVC_COMPILER) && _MSC_VER && !__INTEL_COMPILER 
#  define MSVC_COMPILER 1
#endif

#if MSVC_COMPILER
	// this line only needed for msvc, it does nothing for gcc
#  define DECLSPEC extern "C" __declspec( dllexport )
#else
#  define DECLSPEC
#endif

DECLSPEC const char * regular_greeting();

