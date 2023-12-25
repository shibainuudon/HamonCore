/**
 *	@file	unit_test_ranges_join_view_iterator_post_decrement.cpp
 *
 *	@brief	operator--()のテスト
 *
 *	constexpr iterator operator--(int);
 */

#include <hamon/ranges/adaptors/join_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/array.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_view_test
{
namespace iterator_post_decrement_test
{

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

template <typename T, typename = void>
struct has_post_decrement
	: public hamon::false_type {};

template <typename T>
struct has_post_decrement<T, hamon::void_t<decltype(hamon::declval<T>()--)>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	hamon::array<hamon::array<int, 2>, 3> a
	{{
		{{11, 12}},
		{{21, 22}},
		{{31, 32}},
	}};
	auto rv = a | hamon::views::join;
	using I = decltype(rv.begin());
	using S = decltype(rv.end());
	static_assert(hamon::is_same<I, S>::value, "");
	I it = rv.end();
	static_assert(hamon::is_same<decltype(--it), I&>::value, "");
	VERIFY(it != rv.begin());
	VERIFY(it == rv.end());
	it--;
	VERIFY(*it-- == 32);
	VERIFY(*it-- == 31);
	VERIFY(*it-- == 22);
	VERIFY(*it-- == 21);
	VERIFY(*it-- == 12);
	VERIFY(*it   == 11);
	VERIFY(it == rv.begin());
	VERIFY(it != rv.end());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a0[] = {21,22};
	int a1[] = {23,24,25};
	int a2[] = {26};
	using InnerView = test_bidirectional_common_view<int>;
	using View = test_bidirectional_view<InnerView>;
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	hamon::ranges::join_view<View> rv(v);
	using I = decltype(rv.begin());
	using S = decltype(rv.end());
	static_assert(!hamon::is_same<I, S>::value, "");
	I it = rv.begin();
	static_assert(hamon::is_same<decltype(--it), I&>::value, "");

	++it;
	++it;
	++it;
	++it;
	++it;
	++it;

	VERIFY(it != rv.begin());
	VERIFY(it == rv.end());
	it--;
	VERIFY(*it-- == 26);
	VERIFY(*it-- == 25);
	VERIFY(*it-- == 24);
	VERIFY(*it-- == 23);
	VERIFY(*it-- == 22);
	VERIFY(*it   == 21);
	VERIFY(it == rv.begin());
	VERIFY(it != rv.end());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	// not hamon::is_reference_v<hamon::ranges::range_reference_t<Base>>
	using InnerView = test_bidirectional_common_view<int>;
	using View = test_view<InnerView, ValueBidirectionalIterator<InnerView>>;
	using RV = hamon::ranges::join_view<View>;
	using I = decltype(hamon::declval<RV>().begin());
	static_assert(!has_post_decrement<I>::value, "");
	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	// not hamon::ranges::bidirectional_range<Base>
	using InnerView = test_bidirectional_common_view<int>;
	using View = test_forward_view<InnerView>;
	using RV = hamon::ranges::join_view<View>;
	using I = decltype(hamon::declval<RV>().begin());
	static_assert(!has_post_decrement<I>::value, "");
	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	// not hamon::ranges::bidirectional_range<hamon::ranges::range_reference_t<Base>>
	using InnerView = test_forward_common_view<int>;
	using View = test_bidirectional_view<InnerView>;
	using RV = hamon::ranges::join_view<View>;
	using I = decltype(hamon::declval<RV>().begin());
	static_assert(!has_post_decrement<I>::value, "");
	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	// not hamon::ranges::common_range<hamon::ranges::range_reference_t<Base>>
	using InnerView = test_bidirectional_view<int>;
	using View = test_bidirectional_view<InnerView>;
	using RV = hamon::ranges::join_view<View>;
	using I = decltype(hamon::declval<RV>().begin());
	static_assert(!has_post_decrement<I>::value, "");
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinViewIteratorPostDecrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace iterator_post_decrement_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
