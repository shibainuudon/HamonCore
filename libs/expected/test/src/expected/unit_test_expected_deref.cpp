/**
 *	@file	unit_test_expected_deref.cpp
 *
 *	@brief	operator*() のテスト
 *
 *	constexpr const T& operator*() const & noexcept;
 *	constexpr T& operator*() & noexcept;
 *	constexpr T&& operator*() && noexcept;
 *	constexpr const T&& operator*() const && noexcept;
 */

#include <hamon/expected/expected.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_expected_test
{

namespace deref_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::expected<T, E> const e{T{1}};
		static_assert(noexcept(*e), "");
		auto&& x = *e;
		static_assert(hamon::is_same<decltype(x), T const&>::value, "");
		VERIFY(&x == &(e.value()));
		VERIFY(x == T{1});
	}
	{
		hamon::expected<T, E> e{T{2}};
		static_assert(noexcept(*e), "");
		auto&& x = *e;
		static_assert(hamon::is_same<decltype(x), T&>::value, "");
		VERIFY(&x == &(e.value()));
		VERIFY(x == T{2});
	}
	{
		hamon::expected<T, E> const e{T{3}};
		static_assert(noexcept(*hamon::move(e)), "");
		auto&& x = *hamon::move(e);
		static_assert(hamon::is_same<decltype(x), T const&&>::value, "");
		VERIFY(&x == &(e.value()));
		VERIFY(x == T{3});
	}
	{
		hamon::expected<T, E> e{T{4}};
		static_assert(noexcept(*hamon::move(e)), "");
		auto&& x = *hamon::move(e);
		static_assert(hamon::is_same<decltype(x), T&&>::value, "");
		VERIFY(&x == &(e.value()));
		VERIFY(x == T{4});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ExpectedTest, DerefTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

}	// namespace deref_test

}	// namespace hamon_expected_test
