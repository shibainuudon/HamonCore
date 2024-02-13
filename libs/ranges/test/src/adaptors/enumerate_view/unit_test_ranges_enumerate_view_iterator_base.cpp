/**
 *	@file	unit_test_ranges_enumerate_view_iterator_base.cpp
 *
 *	@brief	base() のテスト
 *
 *	constexpr const iterator_t<Base>& base() const & noexcept;
 *	constexpr iterator_t<Base> base() &&;
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
{
namespace iterator_base_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using EV = hamon::ranges::enumerate_view<V>;
	using I = decltype(hamon::declval<EV&>().begin());
	using BaseIter = hamon::ranges::iterator_t<V>;

	static_assert(hamon::is_same<decltype(hamon::declval<I&>().base()), BaseIter const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I&&>().base()), BaseIter>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&>().base()), BaseIter const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&&>().base()), BaseIter const&>::value, "");

	static_assert( noexcept(hamon::declval<I&>().base()), "");
//	static_assert(!noexcept(hamon::declval<I&&>().base()), "");
	static_assert( noexcept(hamon::declval<I const&>().base()), "");
	static_assert( noexcept(hamon::declval<I const&&>().base()), "");
	
	int a[] = {1,2,3};
	V v(a);
	EV ev(v);
	auto it = ev.begin();
	VERIFY(it.base() == v.begin());
	VERIFY(hamon::move(it).base() == v.begin());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewIteratorBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_base_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
