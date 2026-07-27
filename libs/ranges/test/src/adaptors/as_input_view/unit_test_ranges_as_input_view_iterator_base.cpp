/**
 *	@file	unit_test_ranges_as_input_view_iterator_base.cpp
 *
 *	@brief	base() のテスト
 *
 *	constexpr iterator_t<Base> base() &&;
 *	constexpr const iterator_t<Base>& base() const & noexcept;
 */

#include <hamon/ranges/adaptors/as_input_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace as_input_view_test
{
namespace iterator_base_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class ViewWrapper>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = ViewWrapper<T>;
	using AIV = hamon::ranges::as_input_view<V>;
	using I  = decltype(hamon::declval<AIV&>().begin());
	using BaseIter = hamon::ranges::iterator_t<V>;

	static_assert(hamon::is_same<decltype(hamon::declval<I&>().base()), BaseIter const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I&&>().base()), BaseIter>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&>().base()), BaseIter const&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I const&&>().base()), BaseIter const&>::value, "");

	int a[] = {1,2,3};
	V v(a);
	AIV aiv(v);
	auto it = aiv.begin();
	VERIFY(it.base() == v.begin());
	VERIFY(hamon::move(it).base() == v.begin());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AsInputViewIteratorBaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_input_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_forward_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_bidirectional_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_random_access_view>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00<test_contiguous_view>());
}

}	// namespace iterator_base_test
}	// namespace as_input_view_test
}	// namespace hamon_ranges_test
