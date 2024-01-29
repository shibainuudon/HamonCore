/**
 *	@file	unit_test_ranges_join_with_view_iterator_typedefs.cpp
 *
 *	@brief	join_with_view::iterator のテスト
 *
 *	using iterator_concept = see below;
 *	using iterator_category = see below;	// not always present
 *	using value_type = see below;
 *	using difference_type = see below;
 */

#include <hamon/ranges/adaptors/join_with_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_with_view_test
{
namespace iterator_typedefs_test
{

template <typename T>
struct ValueBidirectionalIterator
{
	T*	m_ptr;
	using iterator_category = hamon::bidirectional_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR ValueBidirectionalIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ValueBidirectionalIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR ValueBidirectionalIterator& operator--() { --m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ValueBidirectionalIterator  operator--(int);
	HAMON_CXX11_CONSTEXPR T                           operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ValueBidirectionalIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ValueBidirectionalIterator& rhs) const { return !(*this == rhs); }
};

template <typename T>
struct ValueForwardIterator
{
	T*	m_ptr;
	using iterator_category = hamon::forward_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	//using pointer           = T*;
	//using reference         = T&;
	HAMON_CXX11_CONSTEXPR ValueForwardIterator() : m_ptr() {}
	explicit HAMON_CXX11_CONSTEXPR ValueForwardIterator(T* ptr) : m_ptr(ptr) {}
	template <typename U>
	HAMON_CXX11_CONSTEXPR ValueForwardIterator(ValueForwardIterator<U> const& u) : m_ptr(u.m_ptr) {}
	HAMON_CXX14_CONSTEXPR ValueForwardIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ValueForwardIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX11_CONSTEXPR T operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ValueForwardIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ValueForwardIterator& rhs) const { return !(*this == rhs); }
};

template <typename T, typename = void>
struct has_iterator_category
	: public hamon::false_type {};

template <typename T>
struct has_iterator_category<T, hamon::void_t<typename T::iterator_category>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool iterator_concept_test()
{
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using View = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>>;
		using View = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using View = test_view<InnerView,
			forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using View = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int,
			ValueBidirectionalIterator<int>,
			ValueBidirectionalIterator<int>>;
		using View = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using View = test_view<InnerView,
			ValueBidirectionalIterator<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using View = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			ValueBidirectionalIterator<int>,
			ValueBidirectionalIterator<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using View = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int, input_iterator_wrapper<int>>;
		using View = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using View = test_view<InnerView, input_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int, ValueForwardIterator<int>>;
		using View = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using View = test_view<InnerView, ValueForwardIterator<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using View = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, ValueForwardIterator<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool iterator_category_test()
{
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using View = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int, input_iterator_wrapper<int>>;
		using View = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(!has_iterator_category<I>::value, "");
	}
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using View = test_view<InnerView, input_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(!has_iterator_category<I>::value, "");
	}
	{
		using InnerView = test_view<int, ValueForwardIterator<int>>;
		using View = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(has_iterator_category<I>::value, "");
	}
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using View = test_view<InnerView, ValueForwardIterator<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(!has_iterator_category<I>::value, "");
	}
	{
		using InnerView = test_view<int, forward_iterator_wrapper<int>>;
		using View = test_view<InnerView, forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<char, forward_iterator_wrapper<char>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::input_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using View = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>>;
		using View = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using View = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using View = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using View = test_view<InnerView,
			forward_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	{
		using InnerView = test_view<int,
			bidirectional_iterator_wrapper<int>,
			bidirectional_iterator_wrapper<int>>;
		using View = test_view<InnerView,
			bidirectional_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int,
			forward_iterator_wrapper<int>,
			forward_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(has_iterator_category<I>::value, "");
		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool value_type_test()
{
	{
		using InnerView = test_view<int, input_iterator_wrapper<int>>;
		using View = test_view<InnerView, input_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::value_type, int>::value, "");
	}
	{
		using InnerView = test_view<char, input_iterator_wrapper<char>>;
		using View = test_view<InnerView, input_iterator_wrapper<InnerView>>;
		using Pattern = test_view<char, forward_iterator_wrapper<char>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::value_type, char>::value, "");
	}
	{
		using InnerView = test_view<char, input_iterator_wrapper<char>>;
		using View = test_view<InnerView, input_iterator_wrapper<InnerView>>;
		using Pattern = test_view<unsigned char, forward_iterator_wrapper<unsigned char>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::value_type, int>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool difference_type_test()
{
	{
		using InnerView = test_view<int, input_iterator_wrapper<int>>;
		using View = test_view<InnerView, input_iterator_wrapper<InnerView>>;
		using Pattern = test_view<int, forward_iterator_wrapper<int>>;
		using JV = hamon::ranges::join_with_view<View, Pattern>;
		using I = hamon::ranges::iterator_t<JV>;
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinWithViewIteratorTypedefsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(iterator_concept_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(iterator_category_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(value_type_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(difference_type_test());
}

}	// namespace iterator_typedefs_test
}	// namespace join_with_view_test
}	// namespace hamon_ranges_test
