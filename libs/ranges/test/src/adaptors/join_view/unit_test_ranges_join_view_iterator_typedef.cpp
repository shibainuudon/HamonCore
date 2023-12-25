/**
 *	@file	unit_test_ranges_join_view_iterator_typedef.cpp
 *
 *	@brief	join_view::iterator のテスト
 */

#include <hamon/ranges/adaptors/join_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_view_test
{
namespace iterator_typedef_test
{

template <typename T, typename = void>
struct has_iterator_category
	: public hamon::false_type {};

template <typename T>
struct has_iterator_category<T, hamon::void_t<typename T::iterator_category>>
	: public hamon::true_type {};

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

template <typename T>
struct ValueBidirectionalIterator
{
	T*	m_ptr;
	using iterator_category = hamon::bidirectional_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	//using pointer           = T*;
	//using reference         = T&;
	HAMON_CXX14_CONSTEXPR ValueBidirectionalIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ValueBidirectionalIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR ValueBidirectionalIterator& operator--() { --m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR ValueBidirectionalIterator  operator--(int);
	HAMON_CXX11_CONSTEXPR T                           operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator==(const ValueBidirectionalIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const ValueBidirectionalIterator& rhs) const { return !(*this == rhs); }
};

template <typename T> using ValueForwardView = test_view<T, ValueForwardIterator<T>>;
template <typename T> using ValueBidirectionalCommonView = test_view<T, ValueBidirectionalIterator<T>, ValueBidirectionalIterator<T>>;

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test_iterator_concept()
{
	{
		using V = test_bidirectional_view<test_bidirectional_common_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V = ValueBidirectionalCommonView<test_bidirectional_common_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
//		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
//		static_assert(hamon::is_same<typename CI::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<ValueBidirectionalCommonView<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_concept, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<test_bidirectional_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<test_bidirectional_common_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<test_forward_common_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<test_forward_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_input_view<test_forward_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		//using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
		//static_assert(hamon::is_same<typename CI::iterator_concept, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<test_input_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_concept, hamon::input_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<ValueForwardView<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_concept, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = ValueForwardView<test_forward_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		//using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
		//static_assert(hamon::is_same<typename CI::iterator_concept, hamon::forward_iterator_tag>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test_iterator_category()
{
	{
		using V = test_bidirectional_view<test_bidirectional_common_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_category, hamon::bidirectional_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_category, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<test_bidirectional_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<test_bidirectional_common_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_bidirectional_view<test_forward_common_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = ValueBidirectionalCommonView<test_bidirectional_common_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
//		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(!has_iterator_category<I>::value, "");
	}
	{
		using V = test_bidirectional_view<ValueBidirectionalCommonView<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_category, hamon::bidirectional_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_category, hamon::bidirectional_iterator_tag>::value, "");
	}
	{
		using V = test_forward_view<test_forward_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = test_input_view<test_forward_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		//using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(!has_iterator_category<I>::value, "");
	}
	{
		using V = test_forward_view<test_input_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(!has_iterator_category<I>::value, "");
		static_assert(!has_iterator_category<CI>::value, "");
	}
	{
		using V = test_forward_view<ValueForwardView<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(hamon::is_same<typename I::iterator_category, hamon::forward_iterator_tag>::value, "");
		static_assert(hamon::is_same<typename CI::iterator_category, hamon::forward_iterator_tag>::value, "");
	}
	{
		using V = ValueForwardView<test_forward_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		//using CI = decltype(hamon::declval<RV const&>().begin());

		static_assert(!has_iterator_category<I>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test_value_type()
{
	{
		using V = test_input_view<test_input_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		static_assert(hamon::is_same<typename I::value_type, int>::value, "");
	}
	{
		using V = test_input_view<test_input_view<float>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		static_assert(hamon::is_same<typename I::value_type, float>::value, "");
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test_difference_type()
{
	{
		using V = test_input_view<test_input_view<int>>;
		using RV = hamon::ranges::join_view<V>;
		using I = decltype(hamon::declval<RV&>().begin());
		static_assert(hamon::is_same<typename I::difference_type, hamon::ptrdiff_t>::value, "");
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinViewIteratorTypedefTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_concept());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_iterator_category());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_value_type());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test_difference_type());
}

}	// namespace iterator_typedef_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
