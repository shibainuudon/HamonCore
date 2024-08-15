/**
 *	@file	unit_test_memory_unique_ptr_arrow.cpp
 *
 *	@brief	operator->のテスト
 *
 *	constexpr pointer operator->() const noexcept;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace arrow_test
{

struct S
{
	int value;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::unique_ptr<S> const up(new S{13});
		VERIFY(up->value == 13);
	}
	return true;
}

#undef VERIFY

template <typename UP, typename = void>
struct is_invocable_arrow : hamon::false_type {};

template <typename UP>
struct is_invocable_arrow<UP,
	hamon::void_t<decltype(hamon::declval<UP>().operator->())>>
	: hamon::true_type {};

GTEST_TEST(UniquePtrTest, ArrowTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	static_assert( is_invocable_arrow<hamon::unique_ptr<int>>::value, "");
	static_assert( is_invocable_arrow<hamon::unique_ptr<int> const>::value, "");
	static_assert( is_invocable_arrow<hamon::unique_ptr<int const>>::value, "");
	static_assert( is_invocable_arrow<hamon::unique_ptr<int const> const>::value, "");
	static_assert(!is_invocable_arrow<hamon::unique_ptr<int[]>>::value, "");
	static_assert(!is_invocable_arrow<hamon::unique_ptr<int[]> const>::value, "");
	static_assert(!is_invocable_arrow<hamon::unique_ptr<int const[]>>::value, "");
	static_assert(!is_invocable_arrow<hamon::unique_ptr<int const[]> const>::value, "");

	{
		using UP = hamon::unique_ptr<int>;
		static_assert( hamon::is_same<int*, decltype(hamon::declval<UP>().operator->())>::value, "");
		static_assert( hamon::is_same<int*, decltype(hamon::declval<UP const>().operator->())>::value, "");
		static_assert( noexcept(hamon::declval<UP>().operator->()), "");
		static_assert( noexcept(hamon::declval<UP const>().operator->()), "");
	}
	{
		using UP = hamon::unique_ptr<float const>;
		static_assert( hamon::is_same<float const*, decltype(hamon::declval<UP>().operator->())>::value, "");
		static_assert( hamon::is_same<float const*, decltype(hamon::declval<UP const>().operator->())>::value, "");
		static_assert( noexcept(hamon::declval<UP>().operator->()), "");
		static_assert( noexcept(hamon::declval<UP const>().operator->()), "");
	}
}

}	// namespace arrow_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
