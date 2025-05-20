/**
 *	@file	unit_test_expected_arrow.cpp
 *
 *	@brief	operator->() のテスト
 *
 *	constexpr const T* operator->() const noexcept;
 *	constexpr T* operator->() noexcept;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace arrow_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::expected<T, E> const e{T{5}};
		static_assert(noexcept(e.operator->()), "");
		auto x = e.operator->();
		static_assert(hamon::is_same<decltype(x), T const*>::value, "");
		VERIFY(x == &(e.value()));
		VERIFY(*x == T{5});
	}
	{
		hamon::expected<T, E> e{T{10}};
		static_assert(noexcept(e.operator->()), "");
		auto x = e.operator->();
		static_assert(hamon::is_same<decltype(x), T*>::value, "");
		VERIFY(x == &(e.value()));
		VERIFY(*x == T{10});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, ArrowTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

}	// namespace arrow_test

}	// namespace hamon_expected_test
