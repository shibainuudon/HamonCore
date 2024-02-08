/**
 *	@file	unit_test_ranges_elements_view_iterator_typedefs.cpp
 *
 *	@brief	elements_view::iterator のテスト
 *
 *	using iterator_concept = see below;
 *	using iterator_category = see below;                // not always present
 *	using value_type = remove_cvref_t<tuple_element_t<N, range_value_t<Base>>>;
 *	using difference_type = range_difference_t<Base>;
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace elements_view_test
{
namespace iterator_typedefs_test
{

template <typename T, typename ValueType = T, typename Reference = T&>
struct TestIterator
{
	T*	m_ptr;

	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = ValueType;
	using difference_type   = short;

	TestIterator& operator++();
	TestIterator  operator++(int);
	Reference     operator*() const;
	bool operator==(const TestIterator& rhs) const;
	bool operator!=(const TestIterator& rhs) const;
};

template <typename T, typename = void>
struct has_iterator_category
	: public hamon::false_type {};

template <typename T>
struct has_iterator_category<T, hamon::void_t<typename T::iterator_category>>
	: public hamon::true_type {};

HAMON_CXX14_CONSTEXPR bool test_iterator_concept()
{
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_input_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_forward_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_bidirectional_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_random_access_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_contiguous_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::random_access_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_iterator_category()
{
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_input_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(!has_iterator_category<I>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_forward_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_bidirectional_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_random_access_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_contiguous_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::random_access_iterator_tag>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple, Tuple&>>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple, Tuple>>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_value_type()
{
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple, Tuple&>>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::value_type, int>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple, Tuple&>>;
		using EV = hamon::ranges::elements_view<V, 1>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::value_type, long>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple, Tuple>>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::value_type, int>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long const>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple, Tuple>>;
		using EV = hamon::ranges::elements_view<V, 1>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::value_type, long>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_difference_type()
{
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_input_view<Tuple>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	{
		using Tuple = hamon::tuple<int, long>;
		using V = test_view<Tuple, TestIterator<Tuple, Tuple, Tuple&>>;
		using EV = hamon::ranges::elements_view<V, 0>;
		using I = hamon::ranges::iterator_t<EV>;
		static_assert(hamon::is_same<typename I::difference_type, short>::value, "");
	}
	return true;
}

GTEST_TEST(RangesTest, ElementsViewIteratorTypedefsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_concept());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_category());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_value_type());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_difference_type());
}

}	// namespace iterator_typedefs_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
