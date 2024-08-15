/**
 *	@file	unit_test_memory_unique_ptr_ctor_pointer_deleter.cpp
 *
 *	@brief	pointerとdeleterを引数に取るコンストラクタのテスト
 *
 *	constexpr unique_ptr(type_identity_t<pointer> p, const D& d) noexcept;
 *	constexpr unique_ptr(type_identity_t<pointer> p, remove_reference_t<D>&& d) noexcept;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/memory/default_delete.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace ctor_pointer_deleter_test
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
	HAMON_CXX11_CONSTEXPR D2(D2&& d) : value(d.value) {}

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete p; }
};

struct D3
{
	int value;

	HAMON_CXX11_CONSTEXPR D3(int v) : value(v) {}

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete[] p; }
};

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
		hamon::default_delete<int> d;
		hamon::unique_ptr<int> up(new int, d);
		VERIFY(up.get() != nullptr);
	}
	{
		hamon::default_delete<int> d;
		hamon::unique_ptr<int> up(new int, hamon::move(d));
		VERIFY(up.get() != nullptr);
	}
	{
		D1 const d{13};
		hamon::unique_ptr<int, D1> up(new int, d);
		VERIFY(up.get() != nullptr);
		VERIFY(up.get_deleter().value == 13);
	}
	{
		D2 d{14};
		hamon::unique_ptr<int, D2> up(new int, hamon::move(d));
		VERIFY(up.get() != nullptr);
		VERIFY(up.get_deleter().value == 14);
	}
	{
		D3 const d{15};
		hamon::unique_ptr<int[], D3> up(new int[5], d);
		VERIFY(up.get() != nullptr);
		VERIFY(up.get_deleter().value == 15);
	}
	{
		hamon::unique_ptr<int[], D3> up(new int[5], D3{16});
		VERIFY(up.get() != nullptr);
		VERIFY(up.get_deleter().value == 16);
	}
	return true;
}

#undef VERIFY

template <bool B, typename UP, typename P, typename D>
void type_traits_test()
{
	static_assert(B == hamon::is_constructible<UP, P, D>::value, "");
	static_assert(B == hamon::is_nothrow_constructible<UP, P, D>::value, "");
	static_assert(    !hamon::is_trivially_constructible<UP, P, D>::value, "");
	static_assert(B == hamon::is_implicitly_constructible<UP, P, D>::value, "");
}

GTEST_TEST(UniquePtrTest, CtorPointerDeleterTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	type_traits_test<true,  hamon::unique_ptr<int, D1>, int*, D1&>();
	type_traits_test<true,  hamon::unique_ptr<int, D1>, int*, D1 const&>();
	type_traits_test<true,  hamon::unique_ptr<int, D1>, int*, D1&&>();
	type_traits_test<true,  hamon::unique_ptr<int, D1>, int*, D1 const&&>();
	type_traits_test<true,  hamon::unique_ptr<int, D1&>, int*, D1&>();
	type_traits_test<false, hamon::unique_ptr<int, D1&>, int*, D1 const&>();
	type_traits_test<false, hamon::unique_ptr<int, D1&>, int*, D1&&>();
	type_traits_test<false, hamon::unique_ptr<int, D1&>, int*, D1 const&&>();
	type_traits_test<true,  hamon::unique_ptr<int, D1 const&>, int*, D1&>();
	type_traits_test<true,  hamon::unique_ptr<int, D1 const&>, int*, D1 const&>();
	type_traits_test<false, hamon::unique_ptr<int, D1 const&>, int*, D1&&>();
	type_traits_test<false, hamon::unique_ptr<int, D1 const&>, int*, D1 const&&>();
	type_traits_test<true,  hamon::unique_ptr<int, D1*>, int*, D1*>();
	type_traits_test<false, hamon::unique_ptr<int, D1*>, int*, D1 const*>();
	type_traits_test<false, hamon::unique_ptr<int, D1*>, int*, D1&>();
	type_traits_test<false, hamon::unique_ptr<int, D1*>, int*, D1 const&>();
	type_traits_test<false, hamon::unique_ptr<int, D1*>, int*, D1&&>();
	type_traits_test<false, hamon::unique_ptr<int, D1*>, int*, D1 const&&>();
	type_traits_test<true,  hamon::unique_ptr<int, D1 const*>, int*, D1*>();
	type_traits_test<true,  hamon::unique_ptr<int, D1 const*>, int*, D1 const*>();
	type_traits_test<false, hamon::unique_ptr<int, D1 const*>, int*, D1&>();
	type_traits_test<false, hamon::unique_ptr<int, D1 const*>, int*, D1 const&>();
	type_traits_test<false, hamon::unique_ptr<int, D1 const*>, int*, D1&&>();
	type_traits_test<false, hamon::unique_ptr<int, D1 const*>, int*, D1 const&&>();
	type_traits_test<false, hamon::unique_ptr<int, D2>, int*, D2&>();
	type_traits_test<false, hamon::unique_ptr<int, D2>, int*, D2 const&>();
	type_traits_test<true,  hamon::unique_ptr<int, D2>, int*, D2&&>();
	type_traits_test<false, hamon::unique_ptr<int, D2>, int*, D2 const&&>();
	type_traits_test<false, hamon::unique_ptr<int, D1>, int const*, D1 const&>();
	type_traits_test<false, hamon::unique_ptr<int, D1>, int const*, D1&&>();
	type_traits_test<true,  hamon::unique_ptr<int const, D1>, int*, D1 const&>();
	type_traits_test<true,  hamon::unique_ptr<int const, D1>, int*, D1&&>();
	type_traits_test<true,  hamon::unique_ptr<int const, D1>, int const*, D1 const&>();
	type_traits_test<true,  hamon::unique_ptr<int const, D1>, int const*, D1&&>();
	type_traits_test<true,  hamon::unique_ptr<Base, D1>, Base*, D1 const&>();
	type_traits_test<true,  hamon::unique_ptr<Base, D1>, Base*, D1&&>();
	type_traits_test<true,  hamon::unique_ptr<Base, D1>, Derived*, D1 const&>();
	type_traits_test<true,  hamon::unique_ptr<Base, D1>, Derived*, D1&&>();
	type_traits_test<false, hamon::unique_ptr<Derived, D1>, Base*, D1 const&>();
	type_traits_test<false, hamon::unique_ptr<Derived, D1>, Base*, D1&&>();
	type_traits_test<true,  hamon::unique_ptr<Derived, D1>, Derived*, D1 const&>();
	type_traits_test<true,  hamon::unique_ptr<Derived, D1>, Derived*, D1&&>();

	type_traits_test<true,  hamon::unique_ptr<int[], D1>, int*, D1&>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1>, int*, D1 const&>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1>, int*, D1&&>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1>, int*, D1 const&&>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1&>, int*, D1&>();
	type_traits_test<false, hamon::unique_ptr<int[], D1&>, int*, D1 const&>();
	type_traits_test<false, hamon::unique_ptr<int[], D1&>, int*, D1&&>();
	type_traits_test<false, hamon::unique_ptr<int[], D1&>, int*, D1 const&&>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1 const&>, int*, D1&>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1 const&>, int*, D1 const&>();
	type_traits_test<false, hamon::unique_ptr<int[], D1 const&>, int*, D1&&>();
	type_traits_test<false, hamon::unique_ptr<int[], D1 const&>, int*, D1 const&&>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1*>, int*, D1*>();
	type_traits_test<false, hamon::unique_ptr<int[], D1*>, int*, D1 const*>();
	type_traits_test<false, hamon::unique_ptr<int[], D1*>, int*, D1&>();
	type_traits_test<false, hamon::unique_ptr<int[], D1*>, int*, D1 const&>();
	type_traits_test<false, hamon::unique_ptr<int[], D1*>, int*, D1&&>();
	type_traits_test<false, hamon::unique_ptr<int[], D1*>, int*, D1 const&&>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1 const*>, int*, D1*>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1 const*>, int*, D1 const*>();
	type_traits_test<false, hamon::unique_ptr<int[], D1 const*>, int*, D1&>();
	type_traits_test<false, hamon::unique_ptr<int[], D1 const*>, int*, D1 const&>();
	type_traits_test<false, hamon::unique_ptr<int[], D1 const*>, int*, D1&&>();
	type_traits_test<false, hamon::unique_ptr<int[], D1 const*>, int*, D1 const&&>();
	type_traits_test<false, hamon::unique_ptr<int[], D2>, int*, D2&>();
	type_traits_test<false, hamon::unique_ptr<int[], D2>, int*, D2 const&>();
	type_traits_test<true,  hamon::unique_ptr<int[], D2>, int*, D2&&>();
	type_traits_test<false, hamon::unique_ptr<int[], D2>, int*, D2 const&&>();
	type_traits_test<false, hamon::unique_ptr<int[], D1>, int const*, D1 const&>();
	type_traits_test<false, hamon::unique_ptr<int[], D1>, int const*, D1&&>();
	type_traits_test<true,  hamon::unique_ptr<int const[], D1>, int*, D1 const&>();
	type_traits_test<true,  hamon::unique_ptr<int const[], D1>, int*, D1&&>();
	type_traits_test<true,  hamon::unique_ptr<int const[], D1>, int const*, D1 const&>();
	type_traits_test<true,  hamon::unique_ptr<int const[], D1>, int const*, D1&&>();
	type_traits_test<true,  hamon::unique_ptr<Base[], D1>, Base*, D1 const&>();
	type_traits_test<true,  hamon::unique_ptr<Base[], D1>, Base*, D1&&>();
	type_traits_test<false, hamon::unique_ptr<Base[], D1>, Derived*, D1 const&>();
	type_traits_test<false, hamon::unique_ptr<Base[], D1>, Derived*, D1&&>();
	type_traits_test<false, hamon::unique_ptr<Derived[], D1>, Base*, D1 const&>();
	type_traits_test<false, hamon::unique_ptr<Derived[], D1>, Base*, D1&&>();
	type_traits_test<true,  hamon::unique_ptr<Derived[], D1>, Derived*, D1 const&>();
	type_traits_test<true,  hamon::unique_ptr<Derived[], D1>, Derived*, D1&&>();
}

}	// namespace ctor_pointer_deleter_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
