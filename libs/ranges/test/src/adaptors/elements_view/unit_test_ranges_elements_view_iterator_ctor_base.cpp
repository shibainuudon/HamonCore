/**
 *	@file	unit_test_ranges_elements_view_iterator_ctor_base.cpp
 *
 *	@brief	iterator_t<Base>を引数に取るコンストラクタのテスト
 *
 *	constexpr explicit iterator(iterator_t<Base> current);
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace elements_view_test
{
namespace iterator_ctor_base_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using Tuple = hamon::tuple<int, long>;
	using V = test_input_view<Tuple>;
	using EV = hamon::ranges::elements_view<V, 0>;
	using I = decltype(hamon::declval<EV&>().begin());
	using BaseIter = hamon::ranges::iterator_t<V>;

	static_assert( hamon::is_constructible<I, BaseIter>::value, "");
	static_assert(!hamon::is_implicitly_constructible<I, BaseIter>::value, "");

	Tuple a[] =
	{
		Tuple{1,2},
		Tuple{3,4},
		Tuple{5,6},
	};
	V v(a);
	I it{v.begin()};
	VERIFY(it.base().m_ptr == &a[0]);
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewIteratorCtorBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_ctor_base_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
