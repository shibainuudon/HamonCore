/**
 *	@file	unit_test_memory_unique_ptr_get.cpp
 *
 *	@brief	get のテスト
 *
 *	constexpr pointer get() const noexcept;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace get_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		auto p = new int{42};
		hamon::unique_ptr<int> up(p);
		VERIFY(up.get() == p);
	}
	{
		auto p = new int[4];
		hamon::unique_ptr<int[]> up(p);
		VERIFY(up.get() == p);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(UniquePtrTest, GetTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	{
		using UP = hamon::unique_ptr<int>;
		static_assert( hamon::is_same<int*, decltype(hamon::declval<UP>().get())>::value, "");
		static_assert( hamon::is_same<int*, decltype(hamon::declval<UP const>().get())>::value, "");
		static_assert( noexcept(hamon::declval<UP>().get()), "");
		static_assert( noexcept(hamon::declval<UP const>().get()), "");
	}
	{
		using UP = hamon::unique_ptr<float const>;
		static_assert( hamon::is_same<float const*, decltype(hamon::declval<UP>().get())>::value, "");
		static_assert( hamon::is_same<float const*, decltype(hamon::declval<UP const>().get())>::value, "");
		static_assert( noexcept(hamon::declval<UP>().get()), "");
		static_assert( noexcept(hamon::declval<UP const>().get()), "");
	}
	{
		using UP = hamon::unique_ptr<int[]>;
		static_assert( hamon::is_same<int*, decltype(hamon::declval<UP>().get())>::value, "");
		static_assert( hamon::is_same<int*, decltype(hamon::declval<UP const>().get())>::value, "");
		static_assert( noexcept(hamon::declval<UP>().get()), "");
		static_assert( noexcept(hamon::declval<UP const>().get()), "");
	}
}

}	// namespace get_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
