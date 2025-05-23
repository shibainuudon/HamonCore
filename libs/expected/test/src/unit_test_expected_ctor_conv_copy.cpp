/**
 *	@file	unit_test_expected_ctor_conv_copy.cpp
 *
 *	@brief	変換コピーコンストラクタのテスト
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/pair.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace ctor_conv_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::expected<T, E> src = T{13};
		hamon::expected<double, double> dst = src;
		VERIFY(src.has_value());
		VERIFY(dst.has_value());
		VERIFY(src.value() == T{13});
		VERIFY(dst.value() == 13.0);
	}
	{
		hamon::expected<T, E> src = hamon::unexpected<E>{E{14}};
		hamon::expected<double, double> dst = src;
		VERIFY(!src.has_value());
		VERIFY(!dst.has_value());
		VERIFY(src.error() == E{14});
		VERIFY(dst.error() == 14.0);
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test2()
{
	using IntPair  = hamon::pair<int, int>;
	using IntTuple = hamon::tuple<int, int>;

	{
		hamon::expected<IntPair, T> src = IntPair{1, 2};
		hamon::expected<IntTuple, T> dst = src;
		VERIFY(src.has_value());
		VERIFY(dst.has_value());
		VERIFY((dst.value() == IntTuple {1, 2}));
	}
	{
		hamon::expected<T, IntPair> src{hamon::unexpect, 1, 2};
		hamon::expected<T, IntTuple> dst = src;
		VERIFY(!src.has_value());
		VERIFY(!dst.has_value());
		VERIFY((dst.error() == IntTuple {1, 2}));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, CtorConvCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2<double>()));
}

}	// namespace ctor_conv_copy_test

}	// namespace hamon_expected_test
