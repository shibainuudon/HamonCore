/**
 *	@file	unit_test_chrono_treat_as_floating_point.cpp
 *
 *	@brief	treat_as_floating_point のテスト
 */

#include <hamon/chrono/treat_as_floating_point.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

namespace treat_as_floating_point_test
{

template <typename T>
void test()
{
	static_assert(hamon::is_base_of<hamon::is_floating_point<T>, hamon::chrono::treat_as_floating_point<T>>::value, "");
	static_assert(hamon::is_floating_point<T>::value == hamon::chrono::treat_as_floating_point<T>::value, "");
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
	static_assert(hamon::is_floating_point_v<T> == hamon::chrono::treat_as_floating_point_v<T>, "");
#endif
}

GTEST_TEST(ChronoTest, TreatAsFloatingPointTest)
{
	test<int>();
	test<unsigned>();
	test<char>();
	test<bool>();
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace treat_as_floating_point_test

}	// namespace hamon_chrono_test
