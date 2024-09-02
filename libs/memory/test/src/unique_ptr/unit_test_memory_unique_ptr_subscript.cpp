/**
 *	@file	unit_test_memory_unique_ptr_subscript.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	constexpr T& operator[](size_t i) const;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/cstddef/size_t.hpp>
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

namespace subscript_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		auto p = new int[3]{1,2,3};
		hamon::unique_ptr<int[]> up(p);
		static_assert( hamon::is_same<int&, decltype(up[0])>::value, "");
#if !defined(HAMON_USE_STD_UNIQUE_PTR)
		static_assert( noexcept(up[0]), "");
#endif
		VERIFY(up[0] == 1);
		VERIFY(up[1] == 2);
		VERIFY(up[2] == 3);
	}
	{
		auto p = new int[3]{1,2,3};
		hamon::unique_ptr<int[]> const up(p);
		static_assert( hamon::is_same<int&, decltype(up[0])>::value, "");
#if !defined(HAMON_USE_STD_UNIQUE_PTR)
		static_assert( noexcept(up[0]), "");
#endif
		VERIFY(up[0] == 1);
		VERIFY(up[1] == 2);
		VERIFY(up[2] == 3);
	}
	{
		auto p = new int[3]{1,2,3};
		hamon::unique_ptr<int const[]> up(p);
		static_assert( hamon::is_same<int const&, decltype(up[0])>::value, "");
#if !defined(HAMON_USE_STD_UNIQUE_PTR)
		static_assert( noexcept(up[0]), "");
#endif
		VERIFY(up[0] == 1);
		VERIFY(up[1] == 2);
		VERIFY(up[2] == 3);
	}
	return true;
}

#undef VERIFY

template <typename UP, typename = void>
struct is_invocable_subscript : hamon::false_type {};

template <typename UP>
struct is_invocable_subscript<UP,
	hamon::void_t<decltype(hamon::declval<UP>()[hamon::declval<hamon::size_t>()])>>
	: hamon::true_type {};

GTEST_TEST(UniquePtrTest, SubscriptTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	static_assert(!is_invocable_subscript<hamon::unique_ptr<int>>::value, "");
	static_assert(!is_invocable_subscript<hamon::unique_ptr<int> const>::value, "");
	static_assert( is_invocable_subscript<hamon::unique_ptr<int[]>>::value, "");
	static_assert( is_invocable_subscript<hamon::unique_ptr<int[]> const>::value, "");
}

}	// namespace subscript_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
