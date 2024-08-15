/**
 *	@file	unit_test_memory_unique_ptr_ctor_pointer.cpp
 *
 *	@brief	pointerを引数に取るコンストラクタのテスト
 *
 *	constexpr explicit unique_ptr(type_identity_t<pointer> p) noexcept;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace ctor_pointer_test
{

struct D1
{
	int value;

	HAMON_CXX11_CONSTEXPR D1() : value(42) {}

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete p; }
};

struct D2
{
	int value;

	HAMON_CXX11_CONSTEXPR D2(int v) : value(v) {}

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete p; }
};

struct Base {};
struct Derived : Base {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::unique_ptr<int> up(new int);
		VERIFY(up.get() != nullptr);
	}
	{
		hamon::unique_ptr<int, D1> up(new int);
		VERIFY(up.get() != nullptr);
		VERIFY(up.get_deleter().value == 42);
	}
	{
		hamon::unique_ptr<int[]> up(new int[3]);
		VERIFY(up.get() != nullptr);
	}
	return true;
}

#undef VERIFY

template <bool B, typename UP, typename P>
void type_traits_test()
{
	static_assert(B == hamon::is_constructible<UP, P>::value, "");
	static_assert(B == hamon::is_nothrow_constructible<UP, P>::value, "");
	static_assert(    !hamon::is_trivially_constructible<UP, P>::value, "");
	static_assert(    !hamon::is_implicitly_constructible<UP, P>::value, "");
}

GTEST_TEST(UniquePtrTest, CtorPointerTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	type_traits_test<true,  hamon::unique_ptr<int>, int*>();
	type_traits_test<false, hamon::unique_ptr<int>, int const*>();
	type_traits_test<true,  hamon::unique_ptr<int const>, int*>();
	type_traits_test<true,  hamon::unique_ptr<int const>, int const*>();
	type_traits_test<false, hamon::unique_ptr<int>, float*>();
	type_traits_test<false, hamon::unique_ptr<int>, int>();
	type_traits_test<true,  hamon::unique_ptr<Base>, Base*>();
	type_traits_test<true,  hamon::unique_ptr<Base>, Derived*>();
	type_traits_test<false, hamon::unique_ptr<Derived>, Base*>();
	type_traits_test<true,  hamon::unique_ptr<Derived>, Derived*>();
	type_traits_test<true,  hamon::unique_ptr<int, D1>, int*>();
	type_traits_test<false, hamon::unique_ptr<int, D1&>, int*>();
	type_traits_test<false, hamon::unique_ptr<int, D1 const&>, int*>();
	type_traits_test<false, hamon::unique_ptr<int, D1*>, int*>();
	type_traits_test<false, hamon::unique_ptr<int, D1 const*>, int*>();
	type_traits_test<false, hamon::unique_ptr<int, D2>, int*>();

	type_traits_test<true,  hamon::unique_ptr<int[]>, int*>();
	type_traits_test<false, hamon::unique_ptr<int[]>, int const*>();
	type_traits_test<true,  hamon::unique_ptr<int const[]>, int*>();
	type_traits_test<true,  hamon::unique_ptr<int const[]>, int const*>();
	type_traits_test<false, hamon::unique_ptr<int[]>, float*>();
	type_traits_test<false, hamon::unique_ptr<int[]>, int>();
	type_traits_test<true,  hamon::unique_ptr<Base[]>, Base*>();
	type_traits_test<false, hamon::unique_ptr<Base[]>, Derived*>();
	type_traits_test<false, hamon::unique_ptr<Derived[]>, Base*>();
	type_traits_test<true,  hamon::unique_ptr<Derived[]>, Derived*>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1>, int*>();
	type_traits_test<false, hamon::unique_ptr<int[], D1&>, int*>();
	type_traits_test<false, hamon::unique_ptr<int[], D1 const&>, int*>();
	type_traits_test<false, hamon::unique_ptr<int[], D1*>, int*>();
	type_traits_test<false, hamon::unique_ptr<int[], D1 const*>, int*>();
	type_traits_test<false, hamon::unique_ptr<int[], D2>, int*>();
}

}	// namespace ctor_pointer_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
