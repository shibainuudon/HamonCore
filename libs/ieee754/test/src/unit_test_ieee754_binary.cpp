/**
 *	@file	unit_test_ieee754_binary.cpp
 *
 *	@brief	binary のテスト
 */

#include <hamon/ieee754/binary.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_ieee754_test
{

namespace binary_test
{

template <typename T>
HAMON_CXX14_CONSTEXPR bool test_impl(T f)
{
	using binary = hamon::ieee754::binary<T>;
	binary b1(f);
	binary b2(b1.sign(), b1.exponent(), b1.fraction());
	return b1.to_uint() == b2.to_uint();
}

template <typename T>
void test()
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(T(+0.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(T(-0.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(T(+0.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(T(-0.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(T(+0.0001)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(T(-0.0001)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(T(+1.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(T(-1.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(T(+1.125)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(T(-1.125)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(T(+123.456)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(T(-123.456)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(T(+1.0 / 3.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(T(-1.0 / 3.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(hamon::numeric_limits<T>::min()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(hamon::numeric_limits<T>::min() * 2));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(hamon::numeric_limits<T>::min() * 3));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(hamon::numeric_limits<T>::min() * 4));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(hamon::numeric_limits<T>::max()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(hamon::numeric_limits<T>::lowest()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl( hamon::numeric_limits<T>::denorm_min()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(-hamon::numeric_limits<T>::denorm_min()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl( hamon::numeric_limits<T>::denorm_min() * 2));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(-hamon::numeric_limits<T>::denorm_min() * 2));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl( hamon::numeric_limits<T>::denorm_min() * 3));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(-hamon::numeric_limits<T>::denorm_min() * 3));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl( hamon::numeric_limits<T>::denorm_min() * 4));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(-hamon::numeric_limits<T>::denorm_min() * 4));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl( hamon::numeric_limits<T>::infinity()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(-hamon::numeric_limits<T>::infinity()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl( hamon::numeric_limits<T>::quiet_NaN()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_impl(-hamon::numeric_limits<T>::quiet_NaN()));
}

GTEST_TEST(IEEE754Test, BinaryTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace binary_test

}	// namespace hamon_ieee754_test
