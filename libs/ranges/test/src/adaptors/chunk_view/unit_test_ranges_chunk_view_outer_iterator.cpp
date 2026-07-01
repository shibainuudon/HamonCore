/**
 *	@file	unit_test_ranges_chunk_view_outer_iterator.cpp
 *
 *	@brief	chunk_view::outer_iterator のテスト
 */

#include <hamon/ranges/adaptors/chunk_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "range_test_helper.hpp"

namespace hamon_ranges_test
{
namespace chunk_view_test
{
namespace outer_iterator_test
{

template <typename T>
struct SizedInputIterator
{
	T*	m_ptr;
	using iterator_category = hamon::input_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR SizedInputIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR SizedInputIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR SizedInputIterator& operator+=(difference_type n) { m_ptr += n; return *this; }
	HAMON_CXX11_CONSTEXPR SizedInputIterator  operator+(difference_type n) const { return {m_ptr + n}; }
	HAMON_CXX14_CONSTEXPR SizedInputIterator& operator--() { --m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR SizedInputIterator  operator--(int) { auto t = *this; --m_ptr; return t; }
	HAMON_CXX14_CONSTEXPR SizedInputIterator& operator-=(difference_type n) { m_ptr -= n; return *this; }
	HAMON_CXX11_CONSTEXPR SizedInputIterator  operator-(difference_type n) const { return {m_ptr - n}; }
	HAMON_CXX11_CONSTEXPR difference_type     operator-(SizedInputIterator const& rhs) const { return m_ptr - rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                  operator*() const { return *m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                  operator[](difference_type i) const { return m_ptr[i]; }
	HAMON_CXX11_CONSTEXPR bool operator==(const SizedInputIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const SizedInputIterator& rhs) const { return m_ptr != rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator< (const SizedInputIterator& rhs) const { return m_ptr <  rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator> (const SizedInputIterator& rhs) const { return m_ptr >  rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator<=(const SizedInputIterator& rhs) const { return m_ptr <= rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator>=(const SizedInputIterator& rhs) const { return m_ptr >= rhs.m_ptr; }
};

template <typename T>
HAMON_CXX14_CONSTEXPR SizedInputIterator<T>
operator+(hamon::ptrdiff_t, SizedInputIterator<T> const&);

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V  = test_input_view<int>;
	using CV = hamon::ranges::chunk_view<V>;
	using I  = decltype(hamon::declval<CV&>().begin());
	//static_assert(hamon::is_same<I, CV::outer_iterator>::value, "");

	static_assert(!has_iterator_category<I>::value, "");
	static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	static_assert(hamon::is_same<typename I::difference_type,  hamon::ptrdiff_t>::value, "");

	static_assert(!hamon::is_default_constructible<I>::value, "");
	static_assert(!hamon::is_copy_constructible<I>::value, "");
	static_assert( hamon::is_move_constructible<I>::value, "");
	static_assert(!hamon::is_copy_assignable<I>::value, "");
	static_assert( hamon::is_move_assignable<I>::value, "");

	static_assert( has_dereference<I&>::value, "");
	static_assert( has_dereference<I const&>::value, "");
	static_assert( has_pre_increment<I&>::value, "");
	static_assert(!has_pre_increment<I const&>::value, "");
	static_assert( has_post_increment<I&>::value, "");
	static_assert(!has_post_increment<I const&>::value, "");
	static_assert(!has_pre_decrement<I&>::value, "");
	static_assert(!has_pre_decrement<I const&>::value, "");
	static_assert(!has_post_decrement<I&>::value, "");
	static_assert(!has_post_decrement<I const&>::value, "");
	static_assert(!has_plus_equal<I&, int>::value, "");
	static_assert(!has_plus_equal<I const&, int>::value, "");
	static_assert(!has_minus_equal<I&, int>::value, "");
	static_assert(!has_minus_equal<I const&, int>::value, "");
	static_assert(!has_subscript<I&>::value, "");
	static_assert(!has_subscript<I const&>::value, "");
	static_assert(!has_plus<I const&, int>::value, "");
	static_assert(!has_plus<int, I const&>::value, "");
	static_assert(!has_minus<I const&, int>::value, "");
	static_assert(!has_minus<int, I const&>::value, "");
	static_assert(!has_minus<I const&, I const&>::value, "");
	static_assert(!has_minus<I const&, hamon::default_sentinel_t>::value, "");
	static_assert(!has_minus<hamon::default_sentinel_t, I const&>::value, "");
	static_assert(!has_eq  <I const&, I const&>::value, "");
	static_assert(!has_neq <I const&, I const&>::value, "");
	static_assert(!has_lt  <I const&, I const&>::value, "");
	static_assert(!has_lteq<I const&, I const&>::value, "");
	static_assert(!has_gt  <I const&, I const&>::value, "");
	static_assert(!has_gteq<I const&, I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(!has_compare_three_way<I const&, I const&>::value, "");
#endif
	static_assert( has_eq <I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_neq<I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_eq <hamon::default_sentinel_t, I const&>::value, "");
	static_assert( has_neq<hamon::default_sentinel_t, I const&>::value, "");

	static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), void>::value, "");

	int a[] = {0,1,2,3,4,5,6};
	V v(a);
	CV cv(v, 3);
	{
		auto it = cv.begin();
		VERIFY(it != cv.end());
		VERIFY(cv.end() != it);
		{
			int expected[] = {0,1,2};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		auto& t1 = ++it;
		VERIFY(it != cv.end());
		VERIFY(cv.end() != it);
		VERIFY(&t1 == &it);
		{
			int expected[] = {3,4,5};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		it++;
		VERIFY(it != cv.end());
		VERIFY(cv.end() != it);
		{
			int expected[] = {6};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		it++;
		VERIFY(it == cv.end());
		VERIFY(cv.end() == it);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V  = test_view<int, SizedInputIterator<int>, SizedInputIterator<int>>;
	using CV = hamon::ranges::chunk_view<V>;
	using I  = decltype(hamon::declval<CV&>().begin());
	//static_assert(hamon::is_same<I, CV::outer_iterator>::value, "");

	static_assert(!has_iterator_category<I>::value, "");
	static_assert(hamon::is_same<typename I::iterator_concept, hamon::input_iterator_tag>::value, "");
	static_assert(hamon::is_same<typename I::difference_type,  hamon::ptrdiff_t>::value, "");

	static_assert(!hamon::is_default_constructible<I>::value, "");
	static_assert(!hamon::is_copy_constructible<I>::value, "");
	static_assert( hamon::is_move_constructible<I>::value, "");
	static_assert(!hamon::is_copy_assignable<I>::value, "");
	static_assert( hamon::is_move_assignable<I>::value, "");

	static_assert( has_dereference<I&>::value, "");
	static_assert( has_dereference<I const&>::value, "");
	static_assert( has_pre_increment<I&>::value, "");
	static_assert(!has_pre_increment<I const&>::value, "");
	static_assert( has_post_increment<I&>::value, "");
	static_assert(!has_post_increment<I const&>::value, "");
	static_assert(!has_pre_decrement<I&>::value, "");
	static_assert(!has_pre_decrement<I const&>::value, "");
	static_assert(!has_post_decrement<I&>::value, "");
	static_assert(!has_post_decrement<I const&>::value, "");
	static_assert(!has_plus_equal<I&, int>::value, "");
	static_assert(!has_plus_equal<I const&, int>::value, "");
	static_assert(!has_minus_equal<I&, int>::value, "");
	static_assert(!has_minus_equal<I const&, int>::value, "");
	static_assert(!has_subscript<I&>::value, "");
	static_assert(!has_subscript<I const&>::value, "");
	static_assert(!has_plus<I const&, int>::value, "");
	static_assert(!has_plus<int, I const&>::value, "");
	static_assert(!has_minus<I const&, int>::value, "");
	static_assert(!has_minus<int, I const&>::value, "");
	static_assert(!has_minus<I const&, I const&>::value, "");
	static_assert( has_minus<I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_minus<hamon::default_sentinel_t, I const&>::value, "");
	static_assert(!has_eq  <I const&, I const&>::value, "");
	static_assert(!has_neq <I const&, I const&>::value, "");
	static_assert(!has_lt  <I const&, I const&>::value, "");
	static_assert(!has_lteq<I const&, I const&>::value, "");
	static_assert(!has_gt  <I const&, I const&>::value, "");
	static_assert(!has_gteq<I const&, I const&>::value, "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(!has_compare_three_way<I const&, I const&>::value, "");
#endif
	static_assert( has_eq <I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_neq<I const&, hamon::default_sentinel_t>::value, "");
	static_assert( has_eq <hamon::default_sentinel_t, I const&>::value, "");
	static_assert( has_neq<hamon::default_sentinel_t, I const&>::value, "");

	static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<I&>()++), void>::value, "");

	int a[] = {0,1,2,3,4,5,6};
	V v(a);
	CV cv(v, 3);
	{
		auto it = cv.begin();
		VERIFY(it != cv.end());
		VERIFY(cv.end() != it);
		VERIFY((it - cv.end()) == -3);
		VERIFY((cv.end() - it) ==  3);
		{
			int expected[] = {0,1,2};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		auto& t1 = ++it;
		VERIFY(it != cv.end());
		VERIFY(cv.end() != it);
		VERIFY((it - cv.end()) == -2);
		VERIFY((cv.end() - it) ==  2);
		VERIFY(&t1 == &it);
		{
			int expected[] = {3,4,5};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		it++;
		VERIFY(it != cv.end());
		VERIFY(cv.end() != it);
		VERIFY((it - cv.end()) == -1);
		VERIFY((cv.end() - it) ==  1);
		{
			int expected[] = {6};
			VERIFY(hamon::ranges::equal(*it, expected));
		}
		it++;
		VERIFY(it == cv.end());
		VERIFY(cv.end() == it);
		VERIFY((it - cv.end()) == 0);
		VERIFY((cv.end() - it) == 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkViewOuterIteratorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace outer_iterator_test
}	// namespace chunk_view_test
}	// namespace hamon_ranges_test
