/**
 *	@file	unit_test_ranges_join_view_iterator_compare.cpp
 *
 *	@brief	operator== のテスト
 *
 *	friend constexpr bool operator==(const iterator& x, const iterator& y);
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
namespace iterator_compare_test
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
struct NonComapableInputIterator
{
	T*	m_ptr;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	//using pointer           = T*;
	//using reference         = T&;
	HAMON_CXX14_CONSTEXPR NonComapableInputIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR void                       operator++(int) { ++m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                         operator*() const { return *m_ptr; }
	//HAMON_CXX11_CONSTEXPR bool operator==(const NonComapableInputIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	//HAMON_CXX11_CONSTEXPR bool operator!=(const NonComapableInputIterator& rhs) const { return !(*this == rhs); }
};

template <typename T, typename = void>
struct has_equal
	: public hamon::false_type {};

template <typename T>
struct has_equal<T, hamon::void_t<decltype(hamon::declval<T>() == hamon::declval<T>())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_not_equal
	: public hamon::false_type {};

template <typename T>
struct has_not_equal<T, hamon::void_t<decltype(hamon::declval<T>() != hamon::declval<T>())>>
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
	auto it3 = rv.begin();
	auto it4 = rv.begin();
	auto it5 = rv.begin();
	it3++;
	it4++;
	it4++;
	it5++;
	it5++;

	VERIFY( (it1 == it1));
	VERIFY( (it1 == it2));
	VERIFY(!(it1 == it3));
	VERIFY(!(it1 == it4));
	VERIFY(!(it1 == it5));
	VERIFY(!(it5 == it1));
	VERIFY(!(it5 == it2));
	VERIFY(!(it5 == it3));
	VERIFY( (it5 == it4));
	VERIFY( (it5 == it5));

	VERIFY(!(it1 != it1));
	VERIFY(!(it1 != it2));
	VERIFY( (it1 != it3));
	VERIFY( (it1 != it4));
	VERIFY( (it1 != it5));
	VERIFY( (it5 != it1));
	VERIFY( (it5 != it2));
	VERIFY( (it5 != it3));
	VERIFY(!(it5 != it4));
	VERIFY(!(it5 != it5));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using InnerView = test_input_view<int>;
	using View = test_forward_view<InnerView>;
	using RV = hamon::ranges::join_view<View>;
	using I = decltype(hamon::declval<RV>().begin());
	static_assert(has_equal<I>::value, "");
	static_assert(has_not_equal<I>::value, "");
	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	// not hamon::is_reference_v<hamon::ranges::range_reference_t<Base>>
	using InnerView = test_input_view<int>;
	using View = test_view<InnerView, ValueForwardIterator<InnerView>>;
	using RV = hamon::ranges::join_view<View>;
	using I = decltype(hamon::declval<RV>().begin());
	static_assert(!has_equal<I>::value, "");
	static_assert(!has_not_equal<I>::value, "");
	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	// not hamon::ranges::forward_range<Base>
	using InnerView = test_input_view<int>;
	using View = test_input_view<InnerView>;
	using RV = hamon::ranges::join_view<View>;
	using I = decltype(hamon::declval<RV>().begin());
	static_assert(!has_equal<I>::value, "");
	static_assert(!has_not_equal<I>::value, "");
	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	// not hamon::equality_comparable<hamon::ranges::iterator_t<hamon::ranges::range_reference_t<Base>>>
	using InnerView = test_view<int, NonComapableInputIterator<int>>;
	using View = test_forward_view<InnerView>;
	using RV = hamon::ranges::join_view<View>;
	using I = decltype(hamon::declval<RV>().begin());
	static_assert(!has_equal<I>::value, "");
	static_assert(!has_not_equal<I>::value, "");
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinViewIteratorCompareTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace iterator_compare_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
