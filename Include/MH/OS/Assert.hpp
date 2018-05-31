
#pragma once


#include "MH/External/fmt.hpp"
#include <cassert>


#if defined(MH_BUILD_DEBUG)
#   define MH_ASSERT(expr)     assert(expr)
#else
#   define MH_ASSERT(expr)
#endif

