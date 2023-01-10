/**
 *	@file	unit_test_config.cpp
 *
 *	@brief	config のテスト
 */

#include <hamon/config.hpp>

#pragma message("HAMON_PLATFORM         = " HAMON_PLATFORM)
#pragma message("HAMON_ARCHITECTURE     = " HAMON_ARCHITECTURE)
#pragma message("HAMON_COMPILER         = " HAMON_COMPILER)
#pragma message("HAMON_COMPILER_VERSION = " HAMON_STRINGIZE(HAMON_COMPILER_VERSION))
#pragma message("HAMON_STDLIB           = " HAMON_STDLIB)
#pragma message("HAMON_CXX_STANDARD     = " HAMON_STRINGIZE(HAMON_CXX_STANDARD))
