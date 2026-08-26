/**
 *	@file	unit_test_memory_unique_ptr_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	constexpr unique_ptr(unique_ptr&& u) noexcept;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/memory/default_delete.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/type_traits/is_implicitly_move_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace ctor_move_test
{

struct D1
{
	int value;

	HAMON_CXX11_CONSTEXPR D1(int v) : value(v) {}
	HAMON_CXX11_CONSTEXPR D1(D1&& d) : value(d.value) {}

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete p; }
};

struct D2
{
	int value;

	HAMON_CXX11_CONSTEXPR D2(int v) : value(v) {}
	HAMON_CXX11_CONSTEXPR D2(D2&&) = delete;

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete p; }
};

struct S
{
	S(S&&) = delete;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::default_delete<int> d;
		hamon::unique_ptr<int> up1(new int, d);
		VERIFY(up1.get() != nullptr);
		hamon::unique_ptr<int> up2(hamon::move(up1));
		VERIFY(up1.get() == nullptr);
		VERIFY(up2.get() != nullptr);
	}
	{
		D1 d{13};
		hamon::unique_ptr<int, D1> up1(new int, hamon::move(d));
		VERIFY(up1.get() != nullptr);
		hamon::unique_ptr<int, D1> up2(hamon::move(up1));
		VERIFY(up1.get() == nullptr);
		VERIFY(up2.get() != nullptr);
		VERIFY(up2.get_deleter().value == 13);
	}
	{
		D1 const d{13};
		hamon::unique_ptr<int, D1 const&> up1(new int, d);
		VERIFY(up1.get() != nullptr);
		hamon::unique_ptr<int, D1 const&> up2(hamon::move(up1));
		VERIFY(up1.get() == nullptr);
		VERIFY(up2.get() != nullptr);
		VERIFY(up2.get_deleter().value == 13);
	}
	{
		hamon::unique_ptr<int[]> up1(new int[3]);
		VERIFY(up1.get() != nullptr);
		hamon::unique_ptr<int[]> up2(hamon::move(up1));
		VERIFY(up1.get() == nullptr);
		VERIFY(up2.get() != nullptr);
	}
	return true;
}

#undef VERIFY

template <bool B, typename UP>
void type_traits_test()
{
	static_assert(B == hamon::is_move_constructible<UP>::value, "");
	static_assert(B == hamon::is_nothrow_move_constructible<UP>::value, "");
	static_assert(    !hamon::is_trivially_move_constructible<UP>::value, "");
	static_assert(B == hamon::is_implicitly_move_constructible<UP>::value, "");
}

GTEST_TEST(UniquePtrTest, CtorMoveTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	type_traits_test<true,  hamon::unique_ptr<int>>();
	type_traits_test<true,  hamon::unique_ptr<S>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1>>();
	type_traits_test<false, hamon::unique_ptr<int, D2>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1&>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1 const&>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1*>>();
	type_traits_test<true,  hamon::unique_ptr<int, D1 const*>>();
	type_traits_test<true,  hamon::unique_ptr<int, void(&)(int*)>>();
	type_traits_test<true,  hamon::unique_ptr<int, void(*)(int*)>>();

	type_traits_test<true,  hamon::unique_ptr<int[]>>();
	type_traits_test<true,  hamon::unique_ptr<S[]>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1>>();
	type_traits_test<false, hamon::unique_ptr<int[], D2>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1&>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1 const&>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1*>>();
	type_traits_test<true,  hamon::unique_ptr<int[], D1 const*>>();
	type_traits_test<true,  hamon::unique_ptr<int[], void(&)(int*)>>();
	type_traits_test<true,  hamon::unique_ptr<int[], void(*)(int*)>>();
}

}	// namespace ctor_move_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
