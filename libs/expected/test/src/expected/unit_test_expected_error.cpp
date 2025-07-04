﻿/**
 *	@file	unit_test_expected_error.cpp
 *
 *	@brief	error() のテスト
 *
 *	constexpr const E& error() const & noexcept;
 *	constexpr E& error() & noexcept;
 *	constexpr E&& error() && noexcept;
 *	constexpr const E&& error() const && noexcept;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace error_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::expected<T, E> const e{hamon::unexpect, E{1}};
		static_assert(noexcept(e.error()), "");
		auto&& x = e.error();
		static_assert(hamon::is_same<decltype(x), E const&>::value, "");
		VERIFY(x == E{1});
	}
	{
		hamon::expected<T, E> e{hamon::unexpect, E{2}};
		static_assert(noexcept(e.error()), "");
		auto&& x = e.error();
		static_assert(hamon::is_same<decltype(x), E&>::value, "");
		VERIFY(x == E{2});
	}
	{
		hamon::expected<T, E> const e{hamon::unexpect, E{3}};
		static_assert(noexcept(hamon::move(e).error()), "");
		auto&& x = hamon::move(e).error();
		static_assert(hamon::is_same<decltype(x), E const&&>::value, "");
		VERIFY(x == E{3});
	}
	{
		hamon::expected<T, E> e{hamon::unexpect, E{4}};
		static_assert(noexcept(hamon::move(e).error()), "");
		auto&& x = hamon::move(e).error();
		static_assert(hamon::is_same<decltype(x), E&&>::value, "");
		VERIFY(x == E{4});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, ErrorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

}	// namespace error_test

}	// namespace hamon_expected_test
