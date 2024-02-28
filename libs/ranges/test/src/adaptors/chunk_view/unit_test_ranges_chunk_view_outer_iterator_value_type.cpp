/**
 *	@file	unit_test_ranges_chunk_view_outer_iterator_value_type.cpp
 *
 *	@brief	chunk_view::outer_iterator::value_type のテスト
 */

#include <hamon/ranges/adaptors/chunk_view.hpp>
#include <hamon/ranges/concepts.hpp>
#include <hamon/cstdint/uintptr_t.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

#include <hamon/ranges/concepts.hpp>

namespace hamon_ranges_test
{
namespace chunk_view_test
{
namespace outer_iterator_value_type_test
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

template <typename T, typename = void>
struct has_begin
	: public hamon::false_type {};

template <typename T>
struct has_begin<T, hamon::void_t<decltype(hamon::declval<T>().begin())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_end
	: public hamon::false_type {};

template <typename T>
struct has_end<T, hamon::void_t<decltype(hamon::declval<T>().end())>>
	: public hamon::true_type {};

template <typename T, typename = void>
struct has_size
	: public hamon::false_type {};

template <typename T>
struct has_size<T, hamon::void_t<decltype(hamon::declval<T>().size())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V  = test_input_view<int>;
	using CV = hamon::ranges::chunk_view<V>;
	using I  = decltype(hamon::declval<CV&>().begin());
	//static_assert(hamon::is_same<I, CV::outer_iterator>::value, "");

	using ValueType = typename I::value_type;

	static_assert( hamon::ranges::input_range_t<ValueType>::value, "");
	static_assert(!hamon::ranges::forward_range_t<ValueType>::value, "");
	static_assert(!hamon::ranges::common_range_t<ValueType>::value, "");
	static_assert( hamon::ranges::view_t<ValueType>::value, "");

	static_assert(!hamon::is_default_constructible<ValueType>::value, "");
	static_assert( hamon::is_copy_constructible<ValueType>::value, "");
	static_assert( hamon::is_move_constructible<ValueType>::value, "");
	static_assert( hamon::is_copy_assignable<ValueType>::value, "");
	static_assert( hamon::is_move_assignable<ValueType>::value, "");

	static_assert( has_begin<ValueType&>::value, "");
	static_assert( has_begin<ValueType const&>::value, "");
	static_assert( has_end<ValueType&>::value, "");
	static_assert( has_end<ValueType const&>::value, "");
	static_assert(!has_size<ValueType&>::value, "");
	static_assert(!has_size<ValueType const&>::value, "");

	static_assert(noexcept(hamon::declval<ValueType&>().begin()), "");
	static_assert(noexcept(hamon::declval<ValueType&>().end()), "");
	static_assert(noexcept(hamon::declval<ValueType const&>().begin()), "");
	static_assert(noexcept(hamon::declval<ValueType const&>().end()), "");

	//static_assert(hamon::is_same<decltype(hamon::declval<ValueType&>().begin()), CV::inner_iterator>::value, "");
	//static_assert(hamon::is_same<decltype(hamon::declval<ValueType const&>().begin()), CV::inner_iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ValueType&>().end()), hamon::default_sentinel_t>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ValueType const&>().end()), hamon::default_sentinel_t>::value, "");

	int a[] = {0,1,2,3,4,5,6,7,8,9};
	V v(a);
	CV cv(v, 3);
	auto it = cv.begin();
	auto x = *it;
	static_assert(hamon::is_same<decltype(x), ValueType>::value, "");
	auto j = x.begin();
	VERIFY(j != x.end());
	VERIFY(*j == 0);
	++j;
	VERIFY(j != x.end());
	VERIFY(*j == 1);
	++j;
	VERIFY(j != x.end());
	VERIFY(*j == 2);
	++j;
	VERIFY(j == x.end());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	using V  = test_view<int, SizedInputIterator<int>, SizedInputIterator<int>>;
	using CV = hamon::ranges::chunk_view<V>;
	using I  = decltype(hamon::declval<CV&>().begin());
	//static_assert(hamon::is_same<I, CV::outer_iterator>::value, "");

	using ValueType = typename I::value_type;

	static_assert( hamon::ranges::input_range_t<ValueType>::value, "");
	static_assert(!hamon::ranges::forward_range_t<ValueType>::value, "");
	static_assert(!hamon::ranges::common_range_t<ValueType>::value, "");
	static_assert( hamon::ranges::view_t<ValueType>::value, "");

	static_assert(!hamon::is_default_constructible<ValueType>::value, "");
	static_assert( hamon::is_copy_constructible<ValueType>::value, "");
	static_assert( hamon::is_move_constructible<ValueType>::value, "");
	static_assert( hamon::is_copy_assignable<ValueType>::value, "");
	static_assert( hamon::is_move_assignable<ValueType>::value, "");

	static_assert( has_begin<ValueType&>::value, "");
	static_assert( has_begin<ValueType const&>::value, "");
	static_assert( has_end<ValueType&>::value, "");
	static_assert( has_end<ValueType const&>::value, "");
	static_assert( has_size<ValueType&>::value, "");
	static_assert( has_size<ValueType const&>::value, "");

	static_assert(noexcept(hamon::declval<ValueType&>().begin()), "");
	static_assert(noexcept(hamon::declval<ValueType&>().end()), "");
	static_assert(noexcept(hamon::declval<ValueType const&>().begin()), "");
	static_assert(noexcept(hamon::declval<ValueType const&>().end()), "");

	//static_assert(hamon::is_same<decltype(hamon::declval<ValueType&>().begin()), CV::inner_iterator>::value, "");
	//static_assert(hamon::is_same<decltype(hamon::declval<ValueType const&>().begin()), CV::inner_iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ValueType&>().end()), hamon::default_sentinel_t>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ValueType const&>().end()), hamon::default_sentinel_t>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ValueType&>().size()), hamon::uintptr_t>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<ValueType const&>().size()), hamon::uintptr_t>::value, "");

	int a[] = {10,20,30,40};
	V v(a);
	CV cv(v, 2);
	auto it = cv.begin();
	auto x = *it;
	static_assert(hamon::is_same<decltype(x), ValueType>::value, "");
	VERIFY(x.size() == 2);
	auto j = x.begin();
	VERIFY(j != x.end());
	VERIFY(*j == 10);
	++j;
	VERIFY(j != x.end());
	VERIFY(*j == 20);
	++j;
	VERIFY(j == x.end());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkViewOuterIteratorValueTypeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace outer_iterator_value_type_test
}	// namespace chunk_view_test
}	// namespace hamon_ranges_test
