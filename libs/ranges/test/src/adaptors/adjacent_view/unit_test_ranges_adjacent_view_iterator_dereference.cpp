/**
 *	@file	unit_test_ranges_adjacent_view_iterator_dereference.cpp
 *
 *	@brief	operator* のテスト
 *
 *	constexpr auto operator*() const;
 */

#include <hamon/ranges/adaptors/adjacent_view.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace adjacent_view_test
{
namespace iterator_dereference_test
{

template <typename T, typename Reference>
struct TestIterator
{
	T*	m_ptr;

	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;

	HAMON_CXX14_CONSTEXPR TestIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR Reference     operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const TestIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const TestIterator& rhs) const { return !(*this == rhs); }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V  = test_view<int, TestIterator<int, int&>>;
		using AV = hamon::ranges::adjacent_view<V, 2>;
		using I  = decltype(hamon::declval<AV&>().begin());
		using Tuple = hamon::tuple<int&, int&>;
		static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), Tuple>::value, "");
		static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), Tuple>::value, "");

		int a[] = {1,2,3,4};
		V v(a);
		AV av(v);
		auto it = av.begin();
		VERIFY(*it == hamon::make_tuple(1, 2));
	}
	{
		using V  = test_view<int, TestIterator<int, int>>;
		using AV = hamon::ranges::adjacent_view<V, 3>;
		using I  = decltype(hamon::declval<AV&>().begin());
		using Tuple = hamon::tuple<int, int, int>;
		static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), Tuple>::value, "");
		static_assert(hamon::is_same<decltype(*hamon::declval<I const&>()), Tuple>::value, "");

		int a[] = {1,2,3,4};
		V v(a);
		AV av(v);
		auto it = av.begin();
		VERIFY(*it == hamon::make_tuple(1, 2, 3));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AdjacentViewIteratorDereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_dereference_test
}	// namespace adjacent_view_test
}	// namespace hamon_ranges_test
