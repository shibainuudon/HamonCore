/**
 *	@file	unit_test_ieee754_binary.cpp
 *
 *	@brief	binary のテスト
 */

#include <hamon/ieee754/binary.hpp>
#include <hamon/cmath.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_ieee754_test
{

namespace binary_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX14_CONSTEXPR bool test_impl(T f)
{
	using binary = hamon::ieee754::binary<T>;
	binary b1(f);

	if (hamon::signbit(f))
	{
		VERIFY(b1.sign() == 1);
	}
	else
	{
		VERIFY(b1.sign() == 0);
	}

	VERIFY(hamon::iszero(f)      == b1.is_zero());
	VERIFY(hamon::issubnormal(f) == b1.is_subnormal());
	VERIFY(hamon::isnormal(f)    == b1.is_normal());
	VERIFY(hamon::isfinite(f)    == b1.is_finite());
	VERIFY(hamon::isinf(f)       == b1.is_infinity());
	VERIFY(hamon::isnan(f)       == b1.is_nan());

	binary b2(b1.sign(), b1.exponent(), b1.fraction());
	VERIFY(b1.to_uint() == b2.to_uint());

	return true;
}

#undef VERIFY

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
