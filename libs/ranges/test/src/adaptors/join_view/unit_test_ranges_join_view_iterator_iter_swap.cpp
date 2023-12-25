/**
 *	@file	unit_test_ranges_join_view_iterator_iter_swap.cpp
 *
 *	@brief	iter_swap のテスト
 *
 *	friend constexpr void iter_swap(const iterator& x, const iterator& y);
 */

#include <hamon/ranges/adaptors/join_view.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_view_test
{
namespace iterator_iter_swap_test
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

template <typename T, typename = void>
struct has_iter_swap
	: public hamon::false_type {};

template <typename T>
struct has_iter_swap<T, hamon::void_t<decltype(hamon::ranges::iter_swap(hamon::declval<T>(), hamon::declval<T>()))>>
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

	auto it1 = rv.begin();
	auto it2 = rv.begin();
	++it2;
	++it2;
	++it2;
	VERIFY(*it1 == 11);
	VERIFY(*it2 == 22);
	//static_assert( noexcept(hamon::ranges::iter_swap(it1, it2)), "");
	hamon::ranges::iter_swap(it1, it2);
	VERIFY(*it1 == 22);
	VERIFY(*it2 == 11);
	VERIFY(a[0][0] == 22);
	VERIFY(a[0][1] == 12);
	VERIFY(a[1][0] == 21);
	VERIFY(a[1][1] == 11);
	VERIFY(a[2][0] == 31);
	VERIFY(a[2][1] == 32);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a0[] = {21,22};
	int a1[] = {23,24,25};
	int a2[] = {26};
	using InnerView = test_forward_view<int>;
	using View = test_forward_view<InnerView>;
	using RV = hamon::ranges::join_view<View>;
	using I = decltype(hamon::declval<RV>().begin());
	static_assert(has_iter_swap<I>::value, "");

	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	RV rv(v);

	auto it1 = rv.begin();
	++it1;
	++it1;
	auto it2 = rv.begin();
	static_assert(!noexcept(hamon::ranges::iter_swap(it1, it2)), "");
	VERIFY(a0[0] == 21);
	VERIFY(a1[0] == 23);
	hamon::ranges::iter_swap(it1, it2);
	VERIFY(a0[0] == 23);
	VERIFY(a1[0] == 21);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using InnerView = test_view<int, ValueForwardIterator<int>>;
	using View = test_forward_view<InnerView>;
	using RV = hamon::ranges::join_view<View>;
	using I = decltype(hamon::declval<RV>().begin());
	static_assert(!has_iter_swap<I>::value, "");
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinViewIteratorIterSwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace iterator_iter_swap_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
