/**
 *	@file	unit_test_memory_unique_ptr_assign_move.cpp
 *
 *	@brief	ムーブ代入のテスト
 *
 *	constexpr unique_ptr& operator=(unique_ptr&& u) noexcept;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_trivially_move_assignable.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace assign_move_test
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

struct S
{
	S& operator=(S&&) = delete;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::unique_ptr<int> up1(new int);
		auto p = up1.get();
		hamon::unique_ptr<int> up2;
		VERIFY(up1.get() != nullptr);
		VERIFY(up2.get() == nullptr);
		up2 = hamon::move(up1);
		VERIFY(up1.get() == nullptr);
		VERIFY(up2.get() == p);
	}
	{
		hamon::unique_ptr<int[]> up1(new int[4]);
		auto p = up1.get();
		hamon::unique_ptr<int[]> up2;
		VERIFY(up1.get() != nullptr);
		VERIFY(up2.get() == nullptr);
		up2 = hamon::move(up1);
		VERIFY(up1.get() == nullptr);
		VERIFY(up2.get() == p);
	}
	return true;
}

#undef VERIFY

template <bool B, typename UP>
void type_traits_test()
{
	static_assert(B == hamon::is_move_assignable<UP>::value, "");
	static_assert(B == hamon::is_nothrow_move_assignable<UP>::value, "");
	static_assert(    !hamon::is_trivially_move_assignable<UP>::value, "");
}

GTEST_TEST(UniquePtrTest, AssignMoveTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	type_traits_test<true,  hamon::unique_ptr<int>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1&>>();
	type_traits_test<false, hamon::unique_ptr<int, D1 const&>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1&&>>();
	type_traits_test<false, hamon::unique_ptr<int, D1 const&&>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1*>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1 const*>>();
	type_traits_test<false, hamon::unique_ptr<int, D2>>();
	type_traits_test<true,  hamon::unique_ptr<int, D2&>>();
	type_traits_test<false, hamon::unique_ptr<int, D2 const&>>();
	type_traits_test<false, hamon::unique_ptr<int, D2&&>>();
	type_traits_test<false, hamon::unique_ptr<int, D2 const&&>>();
	type_traits_test<true,  hamon::unique_ptr<int, D2*>>();
	type_traits_test<true,  hamon::unique_ptr<int, D2 const*>>();
	type_traits_test<true,  hamon::unique_ptr<S>>();

	type_traits_test<true,  hamon::unique_ptr<int[]>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1&>>();
	type_traits_test<false, hamon::unique_ptr<int[], D1 const&>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1&&>>();
	type_traits_test<false, hamon::unique_ptr<int[], D1 const&&>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1*>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1 const*>>();
	type_traits_test<false, hamon::unique_ptr<int[], D2>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D2&>>();
	type_traits_test<false, hamon::unique_ptr<int[], D2 const&>>();
	type_traits_test<false, hamon::unique_ptr<int[], D2&&>>();
	type_traits_test<false, hamon::unique_ptr<int[], D2 const&&>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D2*>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D2 const*>>();
	type_traits_test<true,  hamon::unique_ptr<S[]>>();
}

}	// namespace assign_move_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
