/**
 *	@file	unit_test_ranges_enumerate_view_iterator_typedefs.cpp
 *
 *	@brief	enumerate_view::iterator のテスト
 *
 *	using iterator_category = input_iterator_tag;
 *	using iterator_concept = see below;
 *	using difference_type = range_difference_t<Base>;
 *	using value_type = tuple<difference_type, range_value_t<Base>>;
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
{
namespace iterator_typedefs_test
{

template <typename T, typename Difference>
struct TestIterator
{
	T*	m_ptr;

	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = Difference;

	TestIterator& operator++();
	TestIterator  operator++(int);
	T&            operator*() const;
	bool operator==(const TestIterator& rhs) const;
	bool operator!=(const TestIterator& rhs) const;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test_iterator_category()
{
	{
		using V = test_input_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_iterator_concept()
{
	{
		using V = test_input_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V = test_random_access_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using V = test_contiguous_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_difference_type()
{
	{
		using V = test_view<int, TestIterator<int, hamon::ptrdiff_t>>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	{
		using V = test_view<int, TestIterator<int, short>>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::difference_type, short>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_value_type()
{
	{
		using V = test_input_view<int>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		using D = hamon::ranges::range_difference_t<V>;
		static_assert(hamon::is_same<typename I::value_type, hamon::tuple<D, int>>::value, "");
	}
	{
		using V = test_input_view<char const>;
		using EV = hamon::ranges::enumerate_view<V>;
		using I = hamon::ranges::iterator_t<EV>;
		using D = hamon::ranges::range_difference_t<V>;
		static_assert(hamon::is_same<typename I::value_type, hamon::tuple<D, char>>::value, "");
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewIteratorTypedefsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_category());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_concept());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_difference_type());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_value_type());
}

}	// namespace iterator_typedefs_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
