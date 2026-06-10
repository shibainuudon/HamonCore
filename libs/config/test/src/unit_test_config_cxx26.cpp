/**
 *	@file	unit_test_config_cxx26.cpp
 *
 *	@brief	
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>

namespace hamon_config_cxx26_test
{

#if defined(HAMON_HAS_CXX26_REMOVE_UNDEFINED_BEHAVIOR_FROM_LEXING)
namespace remove_undefined_behavior_from_lexing_test
{

// UB : universal character name accross spliced lines
int \u\
0\
3\
9\
1 = 0;

#define CONCAT(x, y) x ## y
int CONCAT(\, u0393) = 0; // UB: universal character name formed by macro expansion
#undef CONCAT

}	// namespace remove_undefined_behavior_from_lexing_test
#endif

}	// namespace hamon_config_cxx26_test
