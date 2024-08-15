/**
 *	@file	unit_test_memory_unique_ptr_release.cpp
 *
 *	@brief	release のテスト
 *
 *	constexpr pointer release() noexcept;
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

namespace release_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		auto p = new int;
		hamon::unique_ptr<int> up(p);
		VERIFY(up.get() == p);
		static_assert( hamon::is_same<int*, decltype(up.release())>::value, "");
		static_assert( noexcept(up.release()), "");
		auto p2 = up.release();
		VERIFY(up.get() == nullptr);
		VERIFY(p == p2);
		delete p;
	}
	{
		auto p = new int[3];
		hamon::unique_ptr<int[]> up(p);
		VERIFY(up.get() == p);
		static_assert( hamon::is_same<int*, decltype(up.release())>::value, "");
		static_assert( noexcept(up.release()), "");
		auto p2 = up.release();
		VERIFY(up.get() == nullptr);
		VERIFY(p == p2);
		delete[] p;
	}
	return true;
}

#undef VERIFY

template <typename UP, typename = void>
struct is_invocable_release : hamon::false_type {};

template <typename UP>
struct is_invocable_release<UP,
	hamon::void_t<decltype(hamon::declval<UP>().release())>>
	: hamon::true_type {};

GTEST_TEST(UniquePtrTest, ReleaseTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	static_assert( is_invocable_release<hamon::unique_ptr<int>>::value, "");
	static_assert( is_invocable_release<hamon::unique_ptr<int const>>::value, "");
	static_assert(!is_invocable_release<hamon::unique_ptr<int> const>::value, "");
	static_assert(!is_invocable_release<hamon::unique_ptr<int const> const>::value, "");

	static_assert( is_invocable_release<hamon::unique_ptr<int[]>>::value, "");
	static_assert( is_invocable_release<hamon::unique_ptr<int const[]>>::value, "");
	static_assert(!is_invocable_release<hamon::unique_ptr<int[]> const>::value, "");
	static_assert(!is_invocable_release<hamon::unique_ptr<int const[]> const>::value, "");
}

}	// namespace release_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
