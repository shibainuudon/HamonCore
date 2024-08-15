/**
 *	@file	unit_test_memory_unique_ptr_reset.cpp
 *
 *	@brief	reset のテスト
 *
 *	constexpr void reset(pointer p = pointer()) noexcept;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
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

namespace reset_test
{

struct Base
{
	HAMON_CXX20_CONSTEXPR virtual ~Base() {}
};

struct Derived : Base
{
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		auto p = new int;
		hamon::unique_ptr<int> up(p);
		VERIFY(up.get() == p);
		static_assert( hamon::is_same<void, decltype(up.reset())>::value, "");
		static_assert( noexcept(up.reset()), "");
		up.reset();
		VERIFY(up.get() == nullptr);
	}
	{
		hamon::unique_ptr<int> up;
		VERIFY(up.get() == nullptr);
		auto p = new int;
		static_assert( hamon::is_same<void, decltype(up.reset(p))>::value, "");
		static_assert( noexcept(up.reset(p)), "");
		up.reset(p);
		VERIFY(up.get() == p);
	}
	{
		auto p = new int;
		hamon::unique_ptr<int> up(p);
		VERIFY(up.get() == p);
		static_assert( hamon::is_same<void, decltype(up.reset(nullptr))>::value, "");
		static_assert( noexcept(up.reset(nullptr)), "");
		up.reset(nullptr);
		VERIFY(up.get() == nullptr);
	}
	{
		hamon::unique_ptr<int[]> up(new int[3]);
		VERIFY(up.get() != nullptr);
		static_assert( hamon::is_same<void, decltype(up.reset())>::value, "");
		static_assert( noexcept(up.reset()), "");
		up.reset();
		VERIFY(up.get() == nullptr);
	}
	{
		hamon::unique_ptr<int[]> up;
		VERIFY(up.get() == nullptr);
		auto p = new int[4];
		static_assert( hamon::is_same<void, decltype(up.reset(p))>::value, "");
		static_assert( noexcept(up.reset(p)), "");
		up.reset(p);
		VERIFY(up.get() == p);
	}
	{
		hamon::unique_ptr<int[]> up(new int[3]);
		VERIFY(up.get() != nullptr);
		static_assert( hamon::is_same<void, decltype(up.reset(nullptr))>::value, "");
		static_assert( noexcept(up.reset(nullptr)), "");
		up.reset(nullptr);
		VERIFY(up.get() == nullptr);
	}
	return true;
}

#undef VERIFY

template <typename Void, typename UP, typename... Args>
struct is_invocable_reset_impl : hamon::false_type {};

template <typename UP, typename... Args>
struct is_invocable_reset_impl<
	hamon::void_t<decltype(hamon::declval<UP>().reset(hamon::declval<Args>()...))>, UP, Args...>
	: hamon::true_type {};

template <typename UP, typename... Args>
using is_invocable_reset = is_invocable_reset_impl<void, UP, Args...>;

GTEST_TEST(UniquePtrTest, ResetTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	static_assert( is_invocable_reset<hamon::unique_ptr<int>>::value, "");
	static_assert( is_invocable_reset<hamon::unique_ptr<int const>>::value, "");
	static_assert(!is_invocable_reset<hamon::unique_ptr<int> const>::value, "");
	static_assert(!is_invocable_reset<hamon::unique_ptr<int const> const>::value, "");
	static_assert( is_invocable_reset<hamon::unique_ptr<int>, int*>::value, "");
	static_assert(!is_invocable_reset<hamon::unique_ptr<int>, int const*>::value, "");
	static_assert( is_invocable_reset<hamon::unique_ptr<int const>, int*>::value, "");
	static_assert( is_invocable_reset<hamon::unique_ptr<int const>, int const*>::value, "");
	static_assert( is_invocable_reset<hamon::unique_ptr<Base>, Base*>::value, "");
	static_assert( is_invocable_reset<hamon::unique_ptr<Base>, Derived*>::value, "");
	static_assert(!is_invocable_reset<hamon::unique_ptr<Derived>, Base*>::value, "");
	static_assert( is_invocable_reset<hamon::unique_ptr<Derived>, Derived*>::value, "");
	static_assert( is_invocable_reset<hamon::unique_ptr<int>, hamon::nullptr_t>::value, "");

	static_assert( is_invocable_reset<hamon::unique_ptr<int[]>>::value, "");
	static_assert( is_invocable_reset<hamon::unique_ptr<int const[]>>::value, "");
	static_assert(!is_invocable_reset<hamon::unique_ptr<int[]> const>::value, "");
	static_assert(!is_invocable_reset<hamon::unique_ptr<int const[]> const>::value, "");
	static_assert( is_invocable_reset<hamon::unique_ptr<int[]>, int*>::value, "");
	static_assert(!is_invocable_reset<hamon::unique_ptr<int[]>, int const*>::value, "");
	static_assert( is_invocable_reset<hamon::unique_ptr<int const[]>, int*>::value, "");
	static_assert( is_invocable_reset<hamon::unique_ptr<int const[]>, int const*>::value, "");
	static_assert( is_invocable_reset<hamon::unique_ptr<Base[]>, Base*>::value, "");
	static_assert(!is_invocable_reset<hamon::unique_ptr<Base[]>, Derived*>::value, "");
	static_assert(!is_invocable_reset<hamon::unique_ptr<Derived[]>, Base*>::value, "");
	static_assert( is_invocable_reset<hamon::unique_ptr<Derived[]>, Derived*>::value, "");
	static_assert( is_invocable_reset<hamon::unique_ptr<int[]>, hamon::nullptr_t>::value, "");
}

}	// namespace reset_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
