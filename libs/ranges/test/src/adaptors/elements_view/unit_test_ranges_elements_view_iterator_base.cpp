/**
 *	@file	unit_test_ranges_elements_view_iterator_base.cpp
 *
 *	@brief	base() のテスト
 *
 *	constexpr const iterator_t<Base>& base() const & noexcept;
 *	constexpr iterator_t<Base> base() &&;
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace elements_view_test
{
namespace iterator_base_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using Tuple = hamon::tuple<int, long>;
	using V = test_input_view<Tuple>;
	using EV = hamon::ranges::elements_view<V, 0>;
	using I = decltype(hamon::declval<EV&>().begin());
	using BaseIter = hamon::ranges::iterator_t<V>;

	static_assert(hamon::is_same<decltype(hamon::declval<I&>().base()), BaseIter const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I&&>().base()), BaseIter>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&>().base()), BaseIter const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&&>().base()), BaseIter const&>::value, "");
	
	Tuple a[] =
	{
		Tuple{1,2},
		Tuple{3,4},
		Tuple{5,6},
	};
	V v(a);
	EV ev(v);
	auto it = ev.begin();
	VERIFY(it.base() == v.begin());
	VERIFY(hamon::move(it).base() == v.begin());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewIteratorBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_base_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
