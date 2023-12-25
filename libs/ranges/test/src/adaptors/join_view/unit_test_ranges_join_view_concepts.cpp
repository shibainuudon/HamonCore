/**
 *	@file	unit_test_ranges_join_view_concepts.cpp
 *
 *	@brief	join_view のテスト
 */

#include <hamon/ranges/adaptors/join_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_view_test
{
namespace concepts_test
{

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
template <typename T> using ValueBidirectionalView = test_view<T, ValueBidirectionalIterator<T>>;

static_assert(hamon::ranges::forward_range_t<ValueForwardView<int>>::value == true, "");
static_assert(hamon::ranges::bidirectional_range_t<ValueBidirectionalView<int>>::value == true, "");

template <template <typename> class InnerView, template <typename> class OuterView>
HAMON_CXX14_CONSTEXPR bool test00()
{
	using T = int;
	using V = OuterView<InnerView<T>>;
	using RV = hamon::ranges::join_view<V>;
	using IV = hamon::ranges::range_reference_t<V>;

	static_assert(hamon::ranges::range_t<RV>::value == true, "");
	static_assert(hamon::ranges::borrowed_range_t<RV>::value == false, "");
	static_assert(hamon::ranges::sized_range_t<RV>::value == false, "");
//	static_assert(hamon::ranges::output_range_t<RV, T>::value == false, "");
#if !(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 110000))	// TODO
	static_assert(hamon::ranges::input_range_t<RV>::value == true, "");
	static_assert(hamon::ranges::forward_range_t<RV>::value ==
		(hamon::ranges::forward_range_t<V>::value &&
		 hamon::ranges::forward_range_t<IV>::value &&
		 hamon::is_reference<IV>::value), "");
	static_assert(hamon::ranges::bidirectional_range_t<RV>::value ==
		(hamon::ranges::bidirectional_range_t<V>::value &&
		 hamon::ranges::bidirectional_range_t<IV>::value &&
		 hamon::is_reference<IV>::value &&
		 hamon::ranges::common_range_t<IV>::value), "");
#endif
	static_assert(hamon::ranges::random_access_range_t<RV>::value == false, "");
	static_assert(hamon::ranges::contiguous_range_t<RV>::value == false, "");
	static_assert(hamon::ranges::common_range_t<RV>::value ==
		(hamon::ranges::forward_range_t<V>::value &&
		 hamon::ranges::forward_range_t<IV>::value &&
		 hamon::ranges::common_range_t<V>::value &&
		 hamon::ranges::common_range_t<IV>::value), "");
	static_assert(hamon::ranges::viewable_range_t<RV>::value == true, "");
	static_assert(hamon::ranges::view_t<RV>::value == true, "");

	return true;
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class OuterView>
HAMON_CXX14_CONSTEXPR bool test01()
{
	VERIFY(test00<test_input_view, OuterView>());
	VERIFY(test00<test_forward_view, OuterView>());
	VERIFY(test00<test_bidirectional_view, OuterView>());
	VERIFY(test00<test_random_access_view, OuterView>());
//	VERIFY(test00<test_contiguous_view, OuterView>());

	VERIFY(test00<test_input_common_view, OuterView>());
	VERIFY(test00<test_forward_common_view, OuterView>());
	VERIFY(test00<test_bidirectional_common_view, OuterView>());
	VERIFY(test00<test_random_access_common_view, OuterView>());
//	VERIFY(test00<test_contiguous_common_view, OuterView>());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY(test01<test_input_view>());
	VERIFY(test01<test_forward_view>());
	VERIFY(test01<test_bidirectional_view>());
	VERIFY(test01<test_random_access_view>());

	VERIFY(test01<test_input_common_view>());
	VERIFY(test01<test_forward_common_view>());
	VERIFY(test01<test_bidirectional_common_view>());
	VERIFY(test01<test_random_access_common_view>());

	VERIFY(test01<test_random_access_borrowed_view>());
	VERIFY(test01<test_input_sized_view>());

	VERIFY(test01<ValueForwardView>());
	VERIFY(test01<ValueBidirectionalView>());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinViewConceptsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace concepts_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
