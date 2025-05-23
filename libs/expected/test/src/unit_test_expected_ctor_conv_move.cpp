/**
 *	@file	unit_test_expected_ctor_conv_move.cpp
 *
 *	@brief	変換ムーブコンストラクタのテスト
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/unexpected.hpp>
#include <hamon/memory.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace ctor_conv_move_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::expected<T, E> src = T{13};
		hamon::expected<double, double> dst = hamon::move(src);
		VERIFY(src.has_value());
		VERIFY(dst.has_value());
		VERIFY(dst.value() == 13.0);
	}
	{
		hamon::expected<T, E> src = hamon::unexpected<E>{E{14}};
		hamon::expected<double, double> dst = hamon::move(src);
		VERIFY(!src.has_value());
		VERIFY(!dst.has_value());
		VERIFY(dst.error() == 14.0);
	}

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test2()
{
	using UniquePtr = hamon::unique_ptr<int>;
	using SharedPtr = hamon::shared_ptr<int>;

	{
		hamon::expected<UniquePtr, T> src = hamon::make_unique<int>(42);
		hamon::expected<SharedPtr, T> dst = hamon::move(src);
		VERIFY(src.has_value());
		VERIFY(dst.has_value());
		VERIFY(*dst.value() == 42);
		VERIFY(src.value() == nullptr);
	}
	{
		hamon::expected<T, UniquePtr> src{hamon::unexpect, hamon::make_unique<int>(42)};
		hamon::expected<T, SharedPtr> dst = hamon::move(src);
		VERIFY(!src.has_value());
		VERIFY(!dst.has_value());
		VERIFY(*dst.error() == 42);
		VERIFY(src.error() == nullptr);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, CtorConvMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<double>()));
}

}	// namespace ctor_conv_move_test

}	// namespace hamon_expected_test
