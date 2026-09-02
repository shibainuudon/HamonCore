/**
 *	@file	unit_test_charconv.cpp
 *
 *	@brief	charconv のテスト
 */

#include <hamon/charconv.hpp>
#include <hamon/cmath.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "get_random_value.hpp"

namespace hamon_charconv_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// 値を to_chars で文字列として出力し、
// その文字列から from_chars によって値を復元するテスト

template <typename T>
bool integral_test_impl(T x, int base)
{
	char buf[128]{};

	auto ret1 = hamon::to_chars(buf, buf+sizeof(buf), x, base);
	VERIFY(ret1.ec == hamon::errc{});
	VERIFY(ret1);

	T y{};

	auto ret2 = hamon::from_chars(buf, ret1.ptr, y, base);
	VERIFY(ret2.ec == hamon::errc{});
	VERIFY(ret2);

	VERIFY(x == y);

	return true;
}

template <typename T>
bool floating_test_impl(T x, hamon::chars_format fmt)
{
	char buf[128]{};

	auto ret1 = hamon::to_chars(buf, buf+sizeof(buf), x, fmt);
	VERIFY(ret1.ec == hamon::errc{});
	VERIFY(ret1);

	T y{};

	auto ret2 = hamon::from_chars(buf, ret1.ptr, y, fmt);
	VERIFY(ret2.ec == hamon::errc{});
	VERIFY(ret2);

	if (hamon::isnan(x))
	{
		VERIFY(hamon::isnan(y));
	}
	else
	{
		VERIFY(x == y);
	}

	return true;
}

template <typename T>
bool integral_test()
{
	for (int base = 2; base <= 36; ++base)
	{
		VERIFY(integral_test_impl(hamon::numeric_limits<T>::min(), base));
		VERIFY(integral_test_impl(hamon::numeric_limits<T>::max(), base));
		for (int i = 0; i < 100; ++i)
		{
			VERIFY(integral_test_impl(get_random_value<T>(), base));
		}
	}
	return true;
}

template <typename T>
bool floating_test()
{
	const hamon::chars_format fmt_tbl[] =
	{
		hamon::chars_format::scientific,
		//hamon::chars_format::fixed,	// fixed は精度が落ちてしまうので正確な値を復元できない
		hamon::chars_format::hex,
		hamon::chars_format::general,
	};

	for (auto fmt : fmt_tbl)
	{
		VERIFY(floating_test_impl( hamon::numeric_limits<T>::min(), fmt));
		VERIFY(floating_test_impl( hamon::numeric_limits<T>::max(), fmt));
		VERIFY(floating_test_impl( hamon::numeric_limits<T>::lowest(), fmt));
		VERIFY(floating_test_impl( hamon::numeric_limits<T>::epsilon(), fmt));
		VERIFY(floating_test_impl(-hamon::numeric_limits<T>::epsilon(), fmt));
		VERIFY(floating_test_impl( hamon::numeric_limits<T>::denorm_min(), fmt));
		VERIFY(floating_test_impl(-hamon::numeric_limits<T>::denorm_min(), fmt));
		VERIFY(floating_test_impl( hamon::numeric_limits<T>::infinity(), fmt));
		VERIFY(floating_test_impl(-hamon::numeric_limits<T>::infinity(), fmt));
		VERIFY(floating_test_impl( hamon::numeric_limits<T>::quiet_NaN(), fmt));
		VERIFY(floating_test_impl(-hamon::numeric_limits<T>::quiet_NaN(), fmt));
		VERIFY(floating_test_impl( hamon::numeric_limits<T>::signaling_NaN(), fmt));
		VERIFY(floating_test_impl(-hamon::numeric_limits<T>::signaling_NaN(), fmt));
		for (int i = 0; i < 100; ++i)
		{
			VERIFY(floating_test_impl(get_random_value<T>(), fmt));
		}
	}
	return true;
}

#undef VERIFY

GTEST_TEST(CharConvTest, CharConvTest)
{
	EXPECT_TRUE(integral_test<char>());
	EXPECT_TRUE(integral_test<short>());
	EXPECT_TRUE(integral_test<int>());
	EXPECT_TRUE(integral_test<long>());
	EXPECT_TRUE(integral_test<long long>());

	EXPECT_TRUE(integral_test<unsigned char>());
	EXPECT_TRUE(integral_test<unsigned short>());
	EXPECT_TRUE(integral_test<unsigned int>());
	EXPECT_TRUE(integral_test<unsigned long>());
	EXPECT_TRUE(integral_test<unsigned long long>());

	EXPECT_TRUE(floating_test<float>());
	EXPECT_TRUE(floating_test<double>());
//	EXPECT_TRUE(floating_test<long double>());	// TODO
}

}	// namespace hamon_charconv_test
