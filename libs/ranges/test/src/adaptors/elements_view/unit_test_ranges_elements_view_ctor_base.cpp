/**
 *	@file	unit_test_ranges_elements_view_ctor_base.cpp
 *
 *	@brief	baseを引数に取るコンストラクタのテスト
 *
 *	constexpr explicit elements_view(V base);
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace elements_view_test
{
namespace ctor_base_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using Tuple = hamon::tuple<int, long>;
	using V = test_input_view<Tuple>;
	using EV = hamon::ranges::elements_view<V, 0>;

	static_assert( hamon::is_constructible<EV, V>::value, "");
	static_assert(!hamon::is_constructible<EV, int>::value, "");
	static_assert(!hamon::is_constructible<EV, V, V>::value, "");

	static_assert(!hamon::is_implicitly_constructible<EV, V>::value, "");
	
	Tuple a[] =
	{
		Tuple{1,2},
		Tuple{3,4},
		Tuple{5,6},
	};
	V v(a);

	EV ev{v};

	VERIFY(*(ev.begin()) == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewCtorBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace ctor_base_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
