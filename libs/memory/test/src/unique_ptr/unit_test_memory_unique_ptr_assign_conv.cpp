/**
 *	@file	unit_test_memory_unique_ptr_assign_conv.cpp
 *
 *	@brief	変換代入のテスト
 *
 *	template<class U, class E>
 *	constexpr unique_ptr& operator=(unique_ptr<U, E>&& u) noexcept;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace assign_conv_test
{

struct D1
{
	int value;

	HAMON_CXX11_CONSTEXPR D1(int v) : value(v) {}

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete p; }
};

struct D2
{
	int value;

	HAMON_CXX11_CONSTEXPR D2(int v) : value(v) {}
	HAMON_CXX14_CONSTEXPR D2& operator=(D1&& d) { value = d.value; d.value = 0; return *this; }

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete p; }
};

struct Base
{
	HAMON_CXX20_CONSTEXPR virtual ~Base() {}
};

struct Derived : Base
{
	HAMON_CXX20_CONSTEXPR virtual ~Derived() {}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		auto p = new Derived();
		hamon::unique_ptr<Derived> up1(p);
		hamon::unique_ptr<Base> up2;
		VERIFY(up1.get() == p);
		VERIFY(up2.get() == nullptr);
		up2 = hamon::move(up1);
		VERIFY(up1.get() == nullptr);
		VERIFY(up2.get() == p);
	}
	{
		auto p = new int[5];
		hamon::unique_ptr<int[]> up1(p);
		hamon::unique_ptr<int const[]> up2;
		VERIFY(up1.get() == p);
		VERIFY(up2.get() == nullptr);
		up2 = hamon::move(up1);
		VERIFY(up1.get() == nullptr);
		VERIFY(up2.get() == p);
	}
	return true;
}

#undef VERIFY

template <bool B, typename UP1, typename UP2>
void type_traits_test()
{
	static_assert(B == hamon::is_assignable<UP1, UP2&&>::value, "");
	static_assert(B == hamon::is_nothrow_assignable<UP1, UP2&&>::value, "");
	static_assert(    !hamon::is_trivially_assignable<UP1, UP2&&>::value, "");
}

GTEST_TEST(UniquePtrTest, AssignConvTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	type_traits_test<true,  hamon::unique_ptr<int const, D1>, hamon::unique_ptr<int,       D1>>();
	type_traits_test<false, hamon::unique_ptr<int,       D1>, hamon::unique_ptr<int const, D1>>();
	type_traits_test<true,  hamon::unique_ptr<Base,    D1>, hamon::unique_ptr<Derived, D1>>();
	type_traits_test<false, hamon::unique_ptr<Derived, D1>, hamon::unique_ptr<Base,    D1>>();
	type_traits_test<false, hamon::unique_ptr<int, D1>, hamon::unique_ptr<int[], D1>>();
	type_traits_test<false, hamon::unique_ptr<int, D1>, hamon::unique_ptr<int, D2>>();
	type_traits_test<true,  hamon::unique_ptr<int, D2>, hamon::unique_ptr<int, D1>>();

	type_traits_test<true,  hamon::unique_ptr<int const[], D1>, hamon::unique_ptr<int[],       D1>>();
	type_traits_test<false, hamon::unique_ptr<int[],       D1>, hamon::unique_ptr<int const[], D1>>();
	type_traits_test<false, hamon::unique_ptr<Base[],    D1>, hamon::unique_ptr<Derived[], D1>>();
	type_traits_test<false, hamon::unique_ptr<Derived[], D1>, hamon::unique_ptr<Base[],    D1>>();
	type_traits_test<false, hamon::unique_ptr<int[], D1>, hamon::unique_ptr<int, D1>>();
	type_traits_test<false, hamon::unique_ptr<int[], D1>, hamon::unique_ptr<int[], D2>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D2>, hamon::unique_ptr<int[], D1>>();
}

}	// namespace assign_conv_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
