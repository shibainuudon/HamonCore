/**
 *	@file	unit_test_ranges_adjacent_transform_view_iterator_dereference.cpp
 *
 *	@brief	operator* のテスト
 *
 *	constexpr decltype(auto) operator*() const noexcept(see below);
 */

#include <hamon/ranges/adaptors/adjacent_transform_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_transform_view_test
{
namespace iterator_dereference_test
{

struct F1
{
	template <typename T>
	constexpr T operator()(T x) const { return x; }
};

struct F2
{
	template <typename T>
	constexpr T& operator()(T& x) const { return x; }
};

struct Add
{
	constexpr int operator()(int x, int y) const { return x + y; }
};

struct Mul
{
	constexpr int operator()(int x, int y) const { return x * y; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F1, 1>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), int>::value, "");
	}
	{
		using V = test_forward_view<char const>;
		using AV = hamon::ranges::adjacent_transform_view<V, F1, 1>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), char>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, F2, 1>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), int&>::value, "");
	}
	{
		using V = test_forward_view<char const>;
		using AV = hamon::ranges::adjacent_transform_view<V, F2, 1>;
		using I = decltype(hamon::declval<AV&>().begin());
		static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), char const&>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, Add, 2>;
		int a[] = {10,20,30,40};
		V v(a);
		AV av(v, Add{});
		auto it = av.begin();
		VERIFY(*it == 30);
	}
	{
		using V = test_forward_view<int>;
		using AV = hamon::ranges::adjacent_transform_view<V, Mul, 2>;
		int a[] = {10,20,30,40};
		V v(a);
		AV av(v, Mul{});
		auto it = av.begin();
		VERIFY(*it == 200);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentTransformViewIteratorDereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iterator_dereference_test
}	// namespace adjacent_transform_view_test
}	// namespace hamon_ranges_test
