/**
 *	@file	unit_test_ranges_elements_view_iterator_dereference.cpp
 *
 *	@brief	operator* のテスト
 *
 *	constexpr decltype(auto) operator*() const;
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace elements_view_test
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
		using Tuple = hamon::tuple<int, long>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple&>>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), int&>::value, "");

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		EV ev(v);
		auto it = ev.begin();
		VERIFY(*it == 1);
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple&>>;
		using EV = hamon::ranges::elements_view<V, 1>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), long const&>::value, "");

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		EV ev(v);
		auto it = ev.begin();
		VERIFY(*it == 2);
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple>>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), int>::value, "");

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		EV ev(v);
		auto it = ev.begin();
		VERIFY(*it == 1);
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple>>;
		using EV = hamon::ranges::elements_view<V, 1>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<decltype(*hamon::declval<I&>()), long>::value, "");

		Tuple a[] =
		{
			Tuple{1,2},
			Tuple{3,4},
			Tuple{5,6},
		};
		V v(a);
		EV ev(v);
		auto it = ev.begin();
		VERIFY(*it == 2);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewIteratorDereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_dereference_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
