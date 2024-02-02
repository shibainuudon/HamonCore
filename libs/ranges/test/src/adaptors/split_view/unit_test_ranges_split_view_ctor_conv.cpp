/**
 *	@file	unit_test_ranges_split_view_ctor_conv.cpp
 *
 *	@brief	Rangeとvalueを受け取るコンストラクタのテスト
 *
 *	template<forward_range R>
 *	  requires constructible_from<V, views::all_t<R>> &&
 *	    constructible_from<Pattern, single_view<range_value_t<R>>>
 *	constexpr explicit split_view(R&& r, range_value_t<R> e);
 */

#include <hamon/ranges/adaptors/split_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/ranges/factories/single_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace split_view_test
{
namespace ctor_conv_test
{

template <typename T>
struct ConvertibleView : hamon::ranges::view_base
{
	ConvertibleView(hamon::views::all_t<test_input_range<int>>);
	ConvertibleView(hamon::views::all_t<test_forward_range<int>>);
	ConvertibleView(hamon::views::all_t<test_forward_range<char>>);
	T* begin() const;
	T* end()   const;
};

template <typename T>
struct SingleView : hamon::ranges::view_base
{
	SingleView(hamon::ranges::single_view<int>);
	T* begin() const;
	T* end()   const;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = ConvertibleView<int>;
		using P = SingleView<int>;
		using RV = hamon::ranges::split_view<V, P>;

		static_assert(!hamon::is_constructible<RV, test_input_range<int>, int>::value, "");
		static_assert( hamon::is_constructible<RV, test_forward_range<int>, int>::value, "");
		static_assert(!hamon::is_constructible<RV, test_random_access_range<int>, int>::value, "");

		static_assert(!hamon::is_implicitly_constructible<RV, test_forward_range<int>, int>::value, "");
	}

	{
		using V = ConvertibleView<int>;
		using P = SingleView<char>;
		using RV = hamon::ranges::split_view<V, P>;

		static_assert(!hamon::is_constructible<RV, test_forward_range<char>, char>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using A = hamon::array<int, 3>;
	using RV = hamon::ranges::split_view<
		hamon::ranges::ref_view<A>, hamon::ranges::single_view<int>>;

	A a {{ 10, 11, 12 }};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::split_view rv(a, 1);
	static_assert(hamon::is_same<decltype(rv), RV>::value, "");
#else
	RV rv(a, 1);
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SplitViewCtorConvTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ctor_conv_test
}	// namespace split_view_test
}	// namespace hamon_ranges_test
