/**
 *	@file	unit_test_memory_unique_ptr_assign_nullptr.cpp
 *
 *	@brief	nullptr_t代入のテスト
 *
 *	constexpr unique_ptr& operator=(nullptr_t) noexcept;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace assign_nullptr_test
{

struct D1
{
	int value;

	HAMON_CXX11_CONSTEXPR D1(int v) : value(v) {}
	HAMON_CXX14_CONSTEXPR D1& operator=(D1 const& d) { value = d.value; return *this; }
	HAMON_CXX14_CONSTEXPR D1& operator=(D1&& d) { value = d.value; d.value = 0; return *this; }

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete p; }
};

struct D2
{
	int value;

	HAMON_CXX11_CONSTEXPR D2(int v) : value(v) {}
	HAMON_CXX14_CONSTEXPR D2& operator=(D2 const& d) { value = d.value; return *this; }
	HAMON_CXX14_CONSTEXPR D2& operator=(D2&&) = delete;

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete p; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::unique_ptr<int> up(new int);
		VERIFY(up.get() != nullptr);
		up = nullptr;
		VERIFY(up.get() == nullptr);
	}
	{
		hamon::unique_ptr<int[]> up(new int[2]);
		VERIFY(up.get() != nullptr);
		up = nullptr;
		VERIFY(up.get() == nullptr);
	}
	return true;
}

#undef VERIFY

template <bool B, typename UP>
void type_traits_test()
{
	static_assert(B == hamon::is_assignable<UP, hamon::nullptr_t>::value, "");
	static_assert(B == hamon::is_nothrow_assignable<UP, hamon::nullptr_t>::value, "");
	static_assert(    !hamon::is_trivially_assignable<UP, hamon::nullptr_t>::value, "");
}

GTEST_TEST(UniquePtrTest, AssignNullptrTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	type_traits_test<true,  hamon::unique_ptr<int>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1&>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1 const&>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1&&>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1 const&&>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1*>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1 const*>>();
	type_traits_test<true,  hamon::unique_ptr<int, D2>>();
	type_traits_test<true,  hamon::unique_ptr<int, D2&>>();
	type_traits_test<true,  hamon::unique_ptr<int, D2 const&>>();
	type_traits_test<true,  hamon::unique_ptr<int, D2&&>>();
	type_traits_test<true,  hamon::unique_ptr<int, D2 const&&>>();
	type_traits_test<true,  hamon::unique_ptr<int, D2*>>();
	type_traits_test<true,  hamon::unique_ptr<int, D2 const*>>();

	type_traits_test<true,  hamon::unique_ptr<int[]>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1&>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1 const&>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1&&>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1 const&&>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1*>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1 const*>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D2>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D2&>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D2 const&>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D2&&>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D2 const&&>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D2*>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D2 const*>>();
}

}	// namespace assign_nullptr_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
