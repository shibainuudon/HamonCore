/**
 *	@file	unit_test_ranges_lazy_split_view_outer_iterator_value_type.cpp
 *
 *	@brief	outer-iterator::value_typeのテスト
 *
 *	template<bool Const>
 *	struct outer-iterator
 *	{
 *		struct value_type;
 *	};
 */

#include <hamon/ranges/adaptors/lazy_split_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace lazy_split_view_test
{
namespace outer_iterator_value_type_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_forward_view<int>;
		using P = test_forward_view<int>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		using ValueType = typename I::value_type;
		static_assert(hamon::ranges::view_t<ValueType>::value, "");
		static_assert(hamon::is_default_constructible<ValueType>::value, "");
		static_assert(hamon::is_constructible<ValueType, I>::value, "");
		static_assert(!hamon::is_constructible<ValueType, int>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<ValueType&>().begin()), typename RV::inner_iterator<true>>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<ValueType&>().end()), hamon::default_sentinel_t>::value, "");

		ValueType v{};
		auto first = v.begin();
		auto last = v.end();
		(void)first;
		(void)last;
	}
	{
		using V = test_input_view<int>;
		using P = test_forward_static_sized_view<int, 1>;
		using RV = hamon::ranges::lazy_split_view<V, P>;
		using I = hamon::ranges::iterator_t<RV>;
		using ValueType = typename I::value_type;
		static_assert(hamon::ranges::view_t<ValueType>::value, "");
		static_assert(hamon::is_default_constructible<ValueType>::value, "");
		static_assert(hamon::is_constructible<ValueType, I>::value, "");
		static_assert(!hamon::is_constructible<ValueType, int>::value, "");
		//static_assert(hamon::is_same<decltype(hamon::declval<ValueType&>().begin()), typename RV::inner_iterator<false>>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<ValueType&>().end()), hamon::default_sentinel_t>::value, "");

		ValueType v{};
		auto first = v.begin();
		auto last = v.end();
		(void)first;
		(void)last;
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, LazySplitViewOuterIteratorValueTypeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace outer_iterator_value_type_test
}	// namespace lazy_split_view_test
}	// namespace hamon_ranges_test
