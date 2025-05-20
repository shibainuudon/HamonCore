/**
 *	@file	unit_test_expected_void_value.cpp
 *
 *	@brief	value() のテスト
 *
 *	constexpr void value() const &;
 *	constexpr void value() &&;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/bad_expected_access.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace value_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");
	{
		hamon::expected<Void, E> const e;
		static_assert(!noexcept(e.value()), "");
		static_assert(hamon::is_same<decltype(e.value()), void>::value, "");
		e.value();
	}
	{
		hamon::expected<Void, E> e;
		static_assert(!noexcept(e.value()), "");
		static_assert(hamon::is_same<decltype(e.value()), void>::value, "");
		e.value();
	}
	{
		hamon::expected<Void, E> const e;
		static_assert(!noexcept(hamon::move(e).value()), "");
		static_assert(hamon::is_same<decltype(e.value()), void>::value, "");
		hamon::move(e).value();
	}
	{
		hamon::expected<Void, E> e;
		static_assert(!noexcept(hamon::move(e).value()), "");
		static_assert(hamon::is_same<decltype(e.value()), void>::value, "");
		hamon::move(e).value();
	}
	return true;
}

#undef VERIFY

void exceptions_test()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::expected<void, int> const e(hamon::unexpect, 5);
		EXPECT_THROW(e.value(), hamon::bad_expected_access<int>);
		EXPECT_TRUE(!e.has_value());
		EXPECT_TRUE(e.error() == 5);
	}
	{
		hamon::expected<void, int> e(hamon::unexpect, 5);
		EXPECT_THROW(e.value(), hamon::bad_expected_access<int>);
		EXPECT_TRUE(!e.has_value());
		EXPECT_TRUE(e.error() == 5);
	}
	{
		hamon::expected<void, int> const e(hamon::unexpect, 5);
		EXPECT_THROW(hamon::move(e).value(), hamon::bad_expected_access<int>);
		EXPECT_TRUE(!e.has_value());
		EXPECT_TRUE(e.error() == 5);
	}
	{
		hamon::expected<void, int> e(hamon::unexpect, 5);
		EXPECT_THROW(hamon::move(e).value(), hamon::bad_expected_access<int>);
		EXPECT_TRUE(!e.has_value());
		EXPECT_TRUE(e.error() == 5);
	}
#endif
}

GTEST_TEST(ExpectedVoidTest, ValueTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile, int>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile, float>()));

	exceptions_test();
}

}	// namespace value_test

}	// namespace hamon_expected_void_test
