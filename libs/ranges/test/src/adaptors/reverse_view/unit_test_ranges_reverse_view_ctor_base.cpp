/**
 *	@file	unit_test_ranges_reverse_view_ctor_base.cpp
 *
 *	@brief	baseを引数に取るコンストラクタのテスト
 *
 *	constexpr explicit reverse_view(V r);
 */

#include <hamon/ranges/adaptors/reverse_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace reverse_view_test
{
namespace ctor_base_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_bidirectional_view<int>;
	using CV = hamon::ranges::reverse_view<V>;

	static_assert( hamon::is_constructible<CV, V>::value, "");
	static_assert(!hamon::is_constructible<CV, int>::value, "");
	static_assert(!hamon::is_constructible<CV, V, V>::value, "");

	static_assert(!hamon::is_implicitly_constructible<CV, V>::value, "");
	
	int a[] = {1,2,3};
	V v(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::reverse_view cv{v};
	static_assert(hamon::is_same<decltype(cv), CV>::value, "");
#else
	CV cv{v};
#endif

	VERIFY(*(cv.begin()) == 3);
	
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using R = test_bidirectional_range<int>;
	using V = hamon::views::all_t<R>;
	using CV = hamon::ranges::reverse_view<V>;

	static_assert( hamon::is_constructible<CV, R>::value, "");
	static_assert( hamon::is_constructible<CV, V>::value, "");

	static_assert(!hamon::is_implicitly_constructible<CV, R>::value, "");
	static_assert(!hamon::is_implicitly_constructible<CV, V>::value, "");

	int a[] = {1,2,3,4};
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::reverse_view cv{hamon::move(r)};
	static_assert(hamon::is_same<decltype(cv), CV>::value, "");
#else
	CV cv{hamon::move(r)};
#endif

	VERIFY(*(cv.begin()) == 4);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using R = test_bidirectional_range<int>;
	using V = hamon::views::all_t<R&>;
	using CV = hamon::ranges::reverse_view<V>;

	static_assert( hamon::is_constructible<CV, R&>::value, "");
	static_assert( hamon::is_constructible<CV, V>::value, "");

	static_assert(!hamon::is_implicitly_constructible<CV, R&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<CV, V>::value, "");

	int a[] = {1,2,3,4,5};
	R r(a);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	hamon::ranges::reverse_view cv{r};
	static_assert(hamon::is_same<decltype(cv), CV>::value, "");
#else
	CV cv{r};
#endif

	VERIFY(*(cv.begin()) == 5);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ReverseViewCtorBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace ctor_base_test
}	// namespace reverse_view_test
}	// namespace hamon_ranges_test
