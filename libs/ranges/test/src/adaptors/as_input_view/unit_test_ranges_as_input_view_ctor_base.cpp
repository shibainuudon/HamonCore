/**
 *	@file	unit_test_ranges_as_input_view_ctor_base.cpp
 *
 *	@brief	base を引数に取るコンストラクタのテスト
 *
 *	constexpr explicit as_input_view(V base);
 */

#include <hamon/ranges/adaptors/as_input_view.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace as_input_view_test
{
namespace ctor_base_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using AIV = hamon::ranges::as_input_view<V>;

	static_assert( hamon::is_constructible<AIV, V>::value, "");
	static_assert(!hamon::is_constructible<AIV, int>::value, "");
	static_assert(!hamon::is_constructible<AIV, V, V>::value, "");

	static_assert(!hamon::is_nothrow_constructible<AIV, V>::value, "");
	static_assert(!hamon::is_implicitly_constructible<AIV, V>::value, "");
	
	int a[] = {1,2,3};
	V v(a);

	AIV aiv{v};
	VERIFY(*(aiv.begin()) == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AsInputViewCtorBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace ctor_base_test
}	// namespace as_input_view_test
}	// namespace hamon_ranges_test
