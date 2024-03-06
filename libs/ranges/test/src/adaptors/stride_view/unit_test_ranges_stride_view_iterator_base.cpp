/**
 *	@file	unit_test_ranges_stride_view_iterator_base.cpp
 *
 *	@brief	base() のテスト
 *
 *	constexpr iterator_t<Base> base() &&;
 *	constexpr const iterator_t<Base>& base() const & noexcept;
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace stride_view_test
{
namespace iterator_base_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using SV = hamon::ranges::stride_view<V>;
	using I = decltype(hamon::declval<SV&>().begin());
	using BaseIter = hamon::ranges::iterator_t<V>;

	static_assert(hamon::is_same<decltype(hamon::declval<I&>().base()), BaseIter const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I&&>().base()), BaseIter>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&>().base()), BaseIter const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&&>().base()), BaseIter const&>::value, "");
	
	int a[] = {1,2,3,4,5};
	V v(a);
	SV sv(v, 2);
	auto it = sv.begin();
	VERIFY(it.base() == v.begin());
	VERIFY(hamon::move(it).base() == v.begin());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewIteratorBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_base_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
