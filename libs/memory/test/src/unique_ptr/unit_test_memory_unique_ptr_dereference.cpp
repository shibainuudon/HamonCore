/**
 *	@file	unit_test_memory_unique_ptr_dereference.cpp
 *
 *	@brief	operator* のテスト
 *
 *	constexpr add_lvalue_reference_t<T> operator*() const noexcept(see below);
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

namespace dereference_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		auto p = new int;
		*p = 10;
		hamon::unique_ptr<int> up(p);
		VERIFY(*up == 10);
		*up = 42;
		VERIFY(*p == 42);
	}
	return true;
}

#undef VERIFY

template <typename UP, typename = void>
struct is_invocable_dereference : hamon::false_type {};

template <typename UP>
struct is_invocable_dereference<UP,
	hamon::void_t<decltype(hamon::declval<UP>().operator*())>>
	: hamon::true_type {};

GTEST_TEST(UniquePtrTest, DereferenceTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	static_assert( is_invocable_dereference<hamon::unique_ptr<int>>::value, "");
	static_assert( is_invocable_dereference<hamon::unique_ptr<int> const>::value, "");
	static_assert( is_invocable_dereference<hamon::unique_ptr<int const>>::value, "");
	static_assert( is_invocable_dereference<hamon::unique_ptr<int const> const>::value, "");
	static_assert(!is_invocable_dereference<hamon::unique_ptr<int[]>>::value, "");
	static_assert(!is_invocable_dereference<hamon::unique_ptr<int[]> const>::value, "");
	static_assert(!is_invocable_dereference<hamon::unique_ptr<int const[]>>::value, "");
	static_assert(!is_invocable_dereference<hamon::unique_ptr<int const[]> const>::value, "");

	{
		using UP = hamon::unique_ptr<int>;
		static_assert( hamon::is_same<int&, decltype(hamon::declval<UP>().operator*())>::value, "");
		static_assert( hamon::is_same<int&, decltype(hamon::declval<UP const>().operator*())>::value, "");
		static_assert( noexcept(hamon::declval<UP>().operator*()), "");
		static_assert( noexcept(hamon::declval<UP const>().operator*()), "");
	}
	{
		using UP = hamon::unique_ptr<float const>;
		static_assert( hamon::is_same<float const&, decltype(hamon::declval<UP>().operator*())>::value, "");
		static_assert( hamon::is_same<float const&, decltype(hamon::declval<UP const>().operator*())>::value, "");
		static_assert( noexcept(hamon::declval<UP>().operator*()), "");
		static_assert( noexcept(hamon::declval<UP const>().operator*()), "");
	}
}

}	// namespace dereference_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
