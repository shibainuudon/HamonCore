/**
 *	@file	unit_test_iterator_reverse_iterator_sized_sentinel_for.cpp
 *
 *	@brief	sized_sentinel_for のテスト
 *
 *	template<class Iterator1, class Iterator2>
 *	requires (!sized_sentinel_for<Iterator1, Iterator2>)
 *	constexpr bool disable_sized_sentinel_for<
 *		reverse_iterator<Iterator1>,
 *		reverse_iterator<Iterator2>> = true;
 */

#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/concepts/disable_sized_sentinel_for.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace sized_sentinel_for_test {

template <typename T>
struct TestIterator
{
	T*	m_ptr;
	using iterator_category = hamon::random_access_iterator_tag;
	using value_type        = T;
	using difference_type   = hamon::ptrdiff_t;
	using pointer           = T*;
	using reference         = T&;
	HAMON_CXX14_CONSTEXPR TestIterator& operator++() { ++m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestIterator  operator++(int) { auto t = *this; ++m_ptr; return t; }
	//HAMON_CXX14_CONSTEXPR TestIterator& operator+=(difference_type n) { m_ptr += n; return *this; }
	//HAMON_CXX11_CONSTEXPR TestIterator  operator+(difference_type n) const { return {m_ptr + n}; }
	HAMON_CXX14_CONSTEXPR TestIterator& operator--() { --m_ptr; return *this; }
	HAMON_CXX14_CONSTEXPR TestIterator  operator--(int) { auto t = *this; --m_ptr; return t; }
	//HAMON_CXX14_CONSTEXPR TestIterator& operator-=(difference_type n) { m_ptr -= n; return *this; }
	//HAMON_CXX11_CONSTEXPR TestIterator  operator-(difference_type n) const { return {m_ptr - n}; }
	HAMON_CXX11_CONSTEXPR difference_type                 operator-(TestIterator const& rhs) const { return m_ptr - rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR T&                              operator*() const { return *m_ptr; }
	//HAMON_CXX11_CONSTEXPR T&                              operator[](difference_type i) const { return m_ptr[i]; }
	HAMON_CXX11_CONSTEXPR bool operator==(const TestIterator& rhs) const { return m_ptr == rhs.m_ptr; }
	HAMON_CXX11_CONSTEXPR bool operator!=(const TestIterator& rhs) const { return m_ptr != rhs.m_ptr; }
	//HAMON_CXX11_CONSTEXPR bool operator< (const TestIterator& rhs) const { return m_ptr <  rhs.m_ptr; }
	//HAMON_CXX11_CONSTEXPR bool operator> (const TestIterator& rhs) const { return m_ptr >  rhs.m_ptr; }
	//HAMON_CXX11_CONSTEXPR bool operator<=(const TestIterator& rhs) const { return m_ptr <= rhs.m_ptr; }
	//HAMON_CXX11_CONSTEXPR bool operator>=(const TestIterator& rhs) const { return m_ptr >= rhs.m_ptr; }
};

//template <typename T>
//HAMON_CXX14_CONSTEXPR TestIterator<T>
//operator+(hamon::ptrdiff_t, TestIterator<T> const&);

}	// namespace sized_sentinel_for_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test

namespace HAMON_DISABLE_SIZED_SENTINEL_FOR_NAMESPACE
{

template <typename T>
HAMON_SPECIALIZE_DISABLE_SIZED_SENTINEL_FOR(true,
	hamon_iterator_test::reverse_iterator_test::sized_sentinel_for_test::TestIterator<T>,
	hamon_iterator_test::reverse_iterator_test::sized_sentinel_for_test::TestIterator<T>);
}

namespace hamon_iterator_test {
namespace reverse_iterator_test {
namespace sized_sentinel_for_test {

static_assert(!hamon::sized_sentinel_for_t<
	TestIterator<int>,
	TestIterator<int>>::value, "");

static_assert( hamon::sized_sentinel_for_t<
	hamon::reverse_iterator<int*>,
	hamon::reverse_iterator<int*>>::value, "");
static_assert(!hamon::sized_sentinel_for_t<
	hamon::reverse_iterator<bidirectional_iterator_wrapper<int>>,
	hamon::reverse_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( hamon::sized_sentinel_for_t<
	hamon::reverse_iterator<random_access_iterator_wrapper<int>>,
	hamon::reverse_iterator<random_access_iterator_wrapper<int>>>::value, "");
static_assert( hamon::sized_sentinel_for_t<
	hamon::reverse_iterator<contiguous_iterator_wrapper<int>>,
	hamon::reverse_iterator<contiguous_iterator_wrapper<int>>>::value, "");
static_assert(!hamon::sized_sentinel_for_t<
	hamon::reverse_iterator<TestIterator<int>>,
	hamon::reverse_iterator<TestIterator<int>>>::value, "");

}	// namespace sized_sentinel_for_test
}	// namespace reverse_iterator_test
}	// namespace hamon_iterator_test
