/**
 *	@file	unit_test_expected_void_bool.cpp
 *
 *	@brief	operator bool() のテスト
 *
 *	constexpr explicit operator bool() const noexcept;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/expected/unexpect.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_void_test
{

namespace bool_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Void, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	static_assert(hamon::is_void<Void>::value, "");
	static_assert(!hamon::is_convertible<hamon::expected<Void, E>, bool>::value, "");
	{
		hamon::expected<Void, E> const e;
		static_assert(noexcept(static_cast<bool>(e)), "");
		VERIFY(static_cast<bool>(e));
	}
	{
		hamon::expected<Void, E> const e{hamon::unexpect};
		static_assert(noexcept(static_cast<bool>(e)), "");
		VERIFY(!static_cast<bool>(e));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedVoidTest, BoolTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile, int>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void volatile, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<void const volatile, float>()));
}

}	// namespace bool_test

}	// namespace hamon_expected_void_test
