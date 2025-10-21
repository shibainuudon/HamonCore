/**
 *	@file	unit_test_chrono_choose.cpp
 *
 *	@brief	choose のテスト
 */

#include <hamon/chrono/choose.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, ChooseTest)
{
	static_assert(hamon::is_enum<hamon::chrono::choose>::value, "");
}

}	// namespace hamon_chrono_test
