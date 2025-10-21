/**
 *	@file	unit_test_chrono_last_spec.cpp
 *
 *	@brief	last_spec のテスト
 */

#include <hamon/chrono/last_spec.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, LastSpecTest)
{
	using last_spec = hamon::chrono::last_spec;

	static_assert(hamon::is_same<const last_spec, decltype(hamon::chrono::last)>::value, "");

	static_assert(hamon::is_trivially_copyable<last_spec>::value, "");
	static_assert(hamon::is_standard_layout<last_spec>::value, "");
}

}	// namespace hamon_chrono_test
