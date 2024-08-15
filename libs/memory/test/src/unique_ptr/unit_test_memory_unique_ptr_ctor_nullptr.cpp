/**
 *	@file	unit_test_memory_unique_ptr_ctor_nullptr.cpp
 *
 *	@brief	nullptr_tを引数に取るコンストラクタのテスト
 *
 *	constexpr unique_ptr(nullptr_t) noexcept;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
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

namespace ctor_nullptr_test
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

struct S
{
	S() = delete;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::unique_ptr<int> up(nullptr);
		VERIFY(up.get() == nullptr);
	}
	{
		hamon::unique_ptr<int, D1> up(nullptr);
		VERIFY(up.get() == nullptr);
		VERIFY(up.get_deleter().value == 42);
	}
	{
		hamon::unique_ptr<S> up(nullptr);
		VERIFY(up.get() == nullptr);
	}
	{
		hamon::unique_ptr<int[]> up(nullptr);
		VERIFY(up.get() == nullptr);
	}
	{
		hamon::unique_ptr<int[], D1> up(nullptr);
		VERIFY(up.get() == nullptr);
		VERIFY(up.get_deleter().value == 42);
	}
	{
		hamon::unique_ptr<S[]> up(nullptr);
		VERIFY(up.get() == nullptr);
	}
	return true;
}

#undef VERIFY

template <bool B, typename UP>
void type_traits_test()
{
	static_assert(B == hamon::is_constructible<UP, hamon::nullptr_t>::value, "");
	static_assert(B == hamon::is_nothrow_constructible<UP, hamon::nullptr_t>::value, "");
	static_assert(    !hamon::is_trivially_constructible<UP, hamon::nullptr_t>::value, "");
	static_assert(B == hamon::is_implicitly_constructible<UP, hamon::nullptr_t>::value, "");
}

GTEST_TEST(UniquePtrTest, CtorNullptrTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	type_traits_test<true,  hamon::unique_ptr<int>>();
	type_traits_test<true,  hamon::unique_ptr<S>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1>>();
	type_traits_test<false, hamon::unique_ptr<int, D2>>();
	type_traits_test<false, hamon::unique_ptr<int, D1&>>();
	type_traits_test<false, hamon::unique_ptr<int, D1 const&>>();
	type_traits_test<false, hamon::unique_ptr<int, D1*>>();
	type_traits_test<false, hamon::unique_ptr<int, D1 const*>>();
	type_traits_test<false, hamon::unique_ptr<int, void(&)(int*)>>();
	type_traits_test<false, hamon::unique_ptr<int, void(*)(int*)>>();

	type_traits_test<true,  hamon::unique_ptr<int[]>>();
	type_traits_test<true,  hamon::unique_ptr<S[]>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1>>();
	type_traits_test<false, hamon::unique_ptr<int[], D2>>();
	type_traits_test<false, hamon::unique_ptr<int[], D1&>>();
	type_traits_test<false, hamon::unique_ptr<int[], D1 const&>>();
	type_traits_test<false, hamon::unique_ptr<int[], D1*>>();
	type_traits_test<false, hamon::unique_ptr<int[], D1 const*>>();
	type_traits_test<false, hamon::unique_ptr<int[], void(&)(int*)>>();
	type_traits_test<false, hamon::unique_ptr<int[], void(*)(int*)>>();
}

}	// namespace ctor_nullptr_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
