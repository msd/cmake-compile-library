#pragma once

#include <string>

extern "C" __declspec( dllexport ) // this line only needed for msvc, it does nothing for gcc
const char * regular_greeting();
