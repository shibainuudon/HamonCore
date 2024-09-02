/**
 *	@file	unit_test_memory_unique_ptr_ctor_conv.cpp
 *
 *	@brief	変換コンストラクタのテスト
 *
 *	template<class U, class E>
 *	constexpr unique_ptr(unique_ptr<U, E>&& u) noexcept;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace ctor_conv_test
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
	HAMON_CXX11_CONSTEXPR D2(D1 const& d) : value(d.value) {}

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete p; }
};

static_assert( hamon::is_convertible<D1, D2>::value, "");
static_assert(!hamon::is_convertible<D2, D1>::value, "");

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
		hamon::unique_ptr<Base> up2(hamon::move(up1));
		VERIFY(up1.get() == nullptr);
		VERIFY(up2.get() == p);
	}
	{
		auto p = new int[4];
		hamon::unique_ptr<int[]> up1(p);
		hamon::unique_ptr<int const[]> up2(hamon::move(up1));
		VERIFY(up1.get() == nullptr);
		VERIFY(up2.get() == p);
	}
	return true;
}

#undef VERIFY

template <bool B, typename UP1, typename UP2>
void type_traits_test()
{
	static_assert(B == hamon::is_constructible<UP1, UP2>::value, "");
	static_assert(B == hamon::is_nothrow_constructible<UP1, UP2>::value, "");
	static_assert(    !hamon::is_trivially_constructible<UP1, UP2>::value, "");
	static_assert(B == hamon::is_implicitly_constructible<UP1, UP2>::value, "");
}

GTEST_TEST(UniquePtrTest, CtorConvTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	type_traits_test<true,  hamon::unique_ptr<int const, D1>, hamon::unique_ptr<int,       D1>>();
	type_traits_test<false, hamon::unique_ptr<int,       D1>, hamon::unique_ptr<int const, D1>>();
	type_traits_test<true,  hamon::unique_ptr<Base,    D1>, hamon::unique_ptr<Derived, D1>>();
	type_traits_test<false, hamon::unique_ptr<Derived, D1>, hamon::unique_ptr<Base,    D1>>();
	type_traits_test<false, hamon::unique_ptr<int, D1>, hamon::unique_ptr<int[], D1>>();
	type_traits_test<false, hamon::unique_ptr<int, D1>, hamon::unique_ptr<int, D2>>();
	type_traits_test<true,  hamon::unique_ptr<int, D2>, hamon::unique_ptr<int, D1>>();
	type_traits_test<false, hamon::unique_ptr<int, D1&>, hamon::unique_ptr<int, D2&>>();
	type_traits_test<false, hamon::unique_ptr<int, D2&>, hamon::unique_ptr<int, D1&>>();

	type_traits_test<true,  hamon::unique_ptr<int const[], D1>, hamon::unique_ptr<int[],       D1>>();
	type_traits_test<false, hamon::unique_ptr<int[],       D1>, hamon::unique_ptr<int const[], D1>>();
	type_traits_test<false, hamon::unique_ptr<Base[],    D1>, hamon::unique_ptr<Derived[], D1>>();
	type_traits_test<false, hamon::unique_ptr<Derived[], D1>, hamon::unique_ptr<Base[],    D1>>();
	type_traits_test<false, hamon::unique_ptr<int[], D1>, hamon::unique_ptr<int, D1>>();
	type_traits_test<false, hamon::unique_ptr<int[], D1>, hamon::unique_ptr<int[], D2>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D2>, hamon::unique_ptr<int[], D1>>();
	type_traits_test<false, hamon::unique_ptr<int[], D1&>, hamon::unique_ptr<int[], D2&>>();
	type_traits_test<false, hamon::unique_ptr<int[], D2&>, hamon::unique_ptr<int[], D1&>>();
}

}	// namespace ctor_conv_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
