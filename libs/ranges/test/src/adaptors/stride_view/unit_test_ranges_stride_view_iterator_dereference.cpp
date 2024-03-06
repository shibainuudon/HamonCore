/**
 *	@file	unit_test_ranges_stride_view_iterator_dereference.cpp
 *
 *	@brief	operator* のテスト
 *
 *	constexpr decltype(auto) operator*() const { return *current_; }
 */

#include <hamon/ranges/adaptors/stride_view.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace stride_view_test
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
		using V = test_view<int, TestIterator<int, int&>>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), int&>::value, "");

		int a[] = {1,2,3,4,5,6};
		V v(a);
		SV sv(v, 3);
		auto it = sv.begin();
		VERIFY(*it == 1);

		VERIFY(a[0] == 1);
		*it = 42;
		VERIFY(a[0] == 42);
	}
	{
		using V = test_view<long, TestIterator<long, long const&>>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), long const&>::value, "");

		long a[] = {11,12,13};
		V v(a);
		SV sv(v, 3);
		auto it = sv.begin();
		VERIFY(*it == 11);
	}
	{
		using V = test_view<int, TestIterator<int, int>>;
		using SV = hamon::ranges::stride_view<V>;
		using I = decltype(hamon::declval<SV&>().begin());
		static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), int>::value, "");

		int a[] = {1,2,3,4,5,6};
		V v(a);
		SV sv(v, 3);
		auto it = sv.begin();
		VERIFY(*it == 1);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, StrideViewIteratorDereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_dereference_test
}	// namespace stride_view_test
}	// namespace hamon_ranges_test
