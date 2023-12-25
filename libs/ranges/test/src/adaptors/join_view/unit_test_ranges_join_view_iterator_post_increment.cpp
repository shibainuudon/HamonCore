/**
 *	@file	unit_test_ranges_join_view_iterator_post_increment.cpp
 *
 *	@brief	operator++(int)のテスト
 *
 *	constexpr void operator++(int);
 *	constexpr iterator operator++(int);
 */

#include <hamon/ranges/adaptors/join_view.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/array.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_view_test
{
namespace iterator_post_increment_test
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
	auto it = rv.begin();
	VERIFY(it == rv.begin());
	VERIFY(it != rv.end());
	VERIFY(*it   == 11);
	VERIFY(*it++ == 11);
	VERIFY(it != rv.begin());
	VERIFY(it != rv.end());
	VERIFY(*it   == 12);
	VERIFY(*it++ == 12);
	VERIFY(*it++ == 21);
	VERIFY(*it++ == 22);
	VERIFY(*it++ == 31);
	VERIFY(*it++ == 32);
	VERIFY(it != rv.begin());
	VERIFY(it == rv.end());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a0[] = {21,22};
	int a1[] = {23,24,25};
	int a2[] = {26};
	using InnerView = test_forward_view<int>;
	using View = test_forward_view<InnerView>;
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	hamon::ranges::join_view<View> rv(v);
	auto it = rv.begin();
	using I = decltype(it);
	static_assert(hamon::is_same<decltype(it++), I>::value, "");
	
	VERIFY(it == rv.begin());
	VERIFY(it != rv.end());
	VERIFY(*it++ == 21);
	VERIFY(*it++ == 22);
	VERIFY(*it++ == 23);
	VERIFY(*it++ == 24);
	VERIFY(*it++ == 25);
	VERIFY(*it++ == 26);
	VERIFY(it != rv.begin());
	VERIFY(it == rv.end());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	// not hamon::is_reference_v<hamon::ranges::range_reference_t<Base>>
	int a0[] = {21,22};
	int a1[] = {23,24,25};
	int a2[] = {26};
	using InnerView = test_forward_view<int>;
	using View = test_view<InnerView, ValueForwardIterator<InnerView>>;
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	hamon::ranges::join_view<View> rv(v);
	auto it = rv.begin();
	static_assert(hamon::is_same<decltype(it++), void>::value, "");

	VERIFY(it != rv.end());
	it++;
	VERIFY(it != rv.end());
	it++;
	VERIFY(it != rv.end());
	it++;
	VERIFY(it != rv.end());
	it++;
	VERIFY(it != rv.end());
	it++;
	VERIFY(it != rv.end());
	it++;
	VERIFY(it == rv.end());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	// not hamon::ranges::forward_range<Base>
	int a0[] = {21};
	int a1[] = {23,24,25};
	int a2[] = {26};
	using InnerView = test_forward_view<int>;
	using View = test_input_view<InnerView>;
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	hamon::ranges::join_view<View> rv(v);
	auto it = rv.begin();
	static_assert(hamon::is_same<decltype(it++), void>::value, "");

	VERIFY(it != rv.end());
	it++;
	VERIFY(it != rv.end());
	it++;
	VERIFY(it != rv.end());
	it++;
	VERIFY(it != rv.end());
	it++;
	VERIFY(it != rv.end());
	it++;
	VERIFY(it == rv.end());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	// not hamon::ranges::forward_range<hamon::ranges::range_reference_t<Base>>
	int a0[] = {21,22};
	int a1[] = {23,24,25,26};
	int a2[] = {27};
	using InnerView = test_input_view<int>;
	using View = test_forward_view<InnerView>;
	InnerView iv[] = {InnerView{a0}, InnerView{a1}, InnerView{a2}};
	View v(iv);
	hamon::ranges::join_view<View> rv(v);
	auto it = rv.begin();
	static_assert(hamon::is_same<decltype(it++), void>::value, "");

	VERIFY(it != rv.end());
	it++;
	VERIFY(it != rv.end());
	it++;
	VERIFY(it != rv.end());
	it++;
	VERIFY(it != rv.end());
	it++;
	VERIFY(it != rv.end());
	it++;
	VERIFY(it != rv.end());
	it++;
	VERIFY(it != rv.end());
	it++;
	VERIFY(it == rv.end());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinViewIteratorPostIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace iterator_post_increment_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
