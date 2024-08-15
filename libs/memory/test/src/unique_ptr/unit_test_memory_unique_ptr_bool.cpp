/**
 *	@file	unit_test_memory_unique_ptr_bool.cpp
 *
 *	@brief	operator bool のテスト
 *
 *	constexpr explicit operator bool() const noexcept;
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

namespace bool_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::unique_ptr<int> up;
		VERIFY(!up);
	}
	{
		hamon::unique_ptr<int> up(new int);
		VERIFY(static_cast<bool>(up));
	}
	{
		hamon::unique_ptr<int[]> up;
		VERIFY(!up);
	}
	{
		hamon::unique_ptr<int[]> up(new int[5]);
		VERIFY(static_cast<bool>(up));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(UniquePtrTest, BoolTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	{
		using UP = hamon::unique_ptr<int>;
		static_assert( hamon::is_same<bool, decltype(hamon::declval<UP>().operator bool())>::value, "");
		static_assert( hamon::is_same<bool, decltype(hamon::declval<UP const>().operator bool())>::value, "");
		static_assert( noexcept(hamon::declval<UP>().operator bool()), "");
		static_assert( noexcept(hamon::declval<UP const>().operator bool()), "");
	}
	{
		using UP = hamon::unique_ptr<int[]>;
		static_assert( hamon::is_same<bool, decltype(hamon::declval<UP>().operator bool())>::value, "");
		static_assert( hamon::is_same<bool, decltype(hamon::declval<UP const>().operator bool())>::value, "");
		static_assert( noexcept(hamon::declval<UP>().operator bool()), "");
		static_assert( noexcept(hamon::declval<UP const>().operator bool()), "");
	}
}

}	// namespace bool_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
