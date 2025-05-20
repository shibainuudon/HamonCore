/**
 *	@file	unit_test_expected_value.cpp
 *
 *	@brief	value() のテスト
 *
 *	constexpr const T& value() const &;
 *	constexpr T& value() &;
 *	constexpr T&& value() &&;
 *	constexpr const T&& value() const &&;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/expected/bad_expected_access.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace value_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::expected<T, E> const e{T{1}};
		static_assert(!noexcept(e.value()), "");
		auto&& x = e.value();
		static_assert(hamon::is_same<decltype(x), T const&>::value, "");
		VERIFY(&x == &(e.value()));
		VERIFY(x == T{1});
	}
	{
		hamon::expected<T, E> e{T{2}};
		static_assert(!noexcept(e.value()), "");
		auto&& x = e.value();
		static_assert(hamon::is_same<decltype(x), T&>::value, "");
		VERIFY(&x == &(e.value()));
		VERIFY(x == T{2});
	}
	{
		hamon::expected<T, E> const e{T{3}};
		static_assert(!noexcept(hamon::move(e).value()), "");
		auto&& x = hamon::move(e).value();
		static_assert(hamon::is_same<decltype(x), T const&&>::value, "");
		VERIFY(&x == &(e.value()));
		VERIFY(x == T{3});
	}
	{
		hamon::expected<T, E> e{T{4}};
		static_assert(!noexcept(hamon::move(e).value()), "");
		auto&& x = hamon::move(e).value();
		static_assert(hamon::is_same<decltype(x), T&&>::value, "");
		VERIFY(&x == &(e.value()));
		VERIFY(x == T{4});
	}
	return true;
}

#undef VERIFY

void exceptions_test()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::expected<int, int> const e(hamon::unexpect, 5);
		EXPECT_THROW((void)e.value(), hamon::bad_expected_access<int>);
		EXPECT_TRUE(!e.has_value());
		EXPECT_TRUE(e.error() == 5);
	}
	{
		hamon::expected<int, int> e(hamon::unexpect, 5);
		EXPECT_THROW((void)e.value(), hamon::bad_expected_access<int>);
		EXPECT_TRUE(!e.has_value());
		EXPECT_TRUE(e.error() == 5);
	}
	{
		hamon::expected<int, int> const e(hamon::unexpect, 5);
		EXPECT_THROW((void)hamon::move(e).value(), hamon::bad_expected_access<int>);
		EXPECT_TRUE(!e.has_value());
		EXPECT_TRUE(e.error() == 5);
	}
	{
		hamon::expected<int, int> e(hamon::unexpect, 5);
		EXPECT_THROW((void)hamon::move(e).value(), hamon::bad_expected_access<int>);
		EXPECT_TRUE(!e.has_value());
		EXPECT_TRUE(e.error() == 5);
	}

	struct Err
	{
		int t;
		Err() : t(0) {}
		Err(Err&) : t(1) {}
		Err(Err const&) : t(2) {}
		Err(Err&& e) : t(e.t) {}
	};

	{
		hamon::expected<int, Err> const e(hamon::unexpect);
		try
		{
			(void)e.value();
			GTEST_FAIL();
		}
		catch (hamon::bad_expected_access<Err>& ex)
		{
			EXPECT_EQ(2, ex.error().t);
		}
	}
	{
		hamon::expected<int, Err> e(hamon::unexpect);
		try
		{
			(void)e.value();
			GTEST_FAIL();
		}
		catch (hamon::bad_expected_access<Err>& ex)
		{
			EXPECT_EQ(2, ex.error().t);
		}
	}
#endif
}

GTEST_TEST(ExpectedTest, ValueTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	exceptions_test();
}

}	// namespace value_test

}	// namespace hamon_expected_test
