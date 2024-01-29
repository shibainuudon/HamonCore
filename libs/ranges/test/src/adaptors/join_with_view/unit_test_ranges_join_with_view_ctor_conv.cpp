/**
 *	@file	unit_test_ranges_join_with_view_ctor_conv.cpp
 *
 *	@brief	Rangeとvalueを受け取るコンストラクタのテスト
 *
 *	template<input_range R>
 *	  requires constructible_from<V, views::all_t<R>> &&
 *	    constructible_from<Pattern, single_view<range_value_t<InnerRng>>>
 *	constexpr explicit join_with_view(R&& r, range_value_t<InnerRng> e);
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/factories/single_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/array.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace ctor_conv_test
{

template <typename T>
struct ConvertibleView : hamon::ranges::view_base
{
	ConvertibleView(hamon::views::all_t<test_input_range<int>>);
	ConvertibleView(hamon::views::all_t<test_input_range<char>>);
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
		using InnerView = test_input_view<int>;
		using View = ConvertibleView<InnerView>;
		using Pattern = SingleView<int>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;

		static_assert( hamon::is_constructible<JV, test_input_range<int>, int>::value, "");
		static_assert(!hamon::is_constructible<JV, test_forward_range<int>, int>::value, "");
	}

	{
		using InnerView = test_input_view<char>;
		using View = ConvertibleView<InnerView>;
		using Pattern = SingleView<char>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;

		static_assert(!hamon::is_constructible<JV, test_input_range<char>, char>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using A = hamon::array<hamon::array<int, 2>, 3>;
	A a
	{{
		{{11, 12}},
		{{21, 22}},
		{{31, 32}},
	}};

	using JV = hamon::ranges::join_with_view<hamon::ranges::ref_view<A>, hamon::ranges::single_view<int>>;

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::join_with_view jv(a, 1);
	static_assert(hamon::is_same<decltype(jv), JV>::value, "");
#else
	JV jv(a, 1);
#endif

	auto it = jv.begin();
	VERIFY(*it++ == 11);
	VERIFY(*it++ == 12);
	VERIFY(*it++ ==  1);
	VERIFY(*it++ == 21);
	VERIFY(*it++ == 22);
	VERIFY(*it++ ==  1);
	VERIFY(*it++ == 31);
	VERIFY(*it++ == 32);
	VERIFY(it == jv.end());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinWithViewCtorConvTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
#if defined(HAMON_HAS_CXX20_CONSTEXPR_UNION)
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test01());
#else
	EXPECT_TRUE(test01());
#endif
}

}	// namespace ctor_conv_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
