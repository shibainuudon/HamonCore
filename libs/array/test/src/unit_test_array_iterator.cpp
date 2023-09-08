/**
 *	@file	unit_test_array_iterator.cpp
 *
 *	@brief	イテレータのテスト
 *
 *	iterator
 *	const_iterator
 *	reverse_iterator
 *	const_reverse_iterator
 */

#include <hamon/array/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/concepts.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_array_test
{

namespace iterator_test
{

template <typename T, hamon::size_t N>
void IteratorTest()
{
	using Array = hamon::array<T, N>;

	using Iterator             = typename Array::iterator;
	using ConstIterator        = typename Array::const_iterator;
	using ReverseIterator      = typename Array::reverse_iterator;
	using ConstReverseIterator = typename Array::const_reverse_iterator;

	{
		using Traits = hamon::iterator_traits<Iterator>;
		static_assert((hamon::is_same<typename Traits::iterator_category, hamon::random_access_iterator_tag>::value), "");
		static_assert((hamon::is_same<typename Traits::value_type,      typename Array::value_type>::value), "");
		static_assert((hamon::is_same<typename Traits::reference,       typename Array::reference>::value), "");
		static_assert((hamon::is_same<typename Traits::pointer,         typename Array::pointer>::value), "");
		static_assert((hamon::is_same<typename Traits::difference_type, typename Array::difference_type>::value), "");
	}
	{
		using Traits = hamon::iterator_traits<ConstIterator>;
		static_assert((hamon::is_same<typename Traits::iterator_category, hamon::random_access_iterator_tag>::value), "");
		static_assert((hamon::is_same<typename Traits::value_type,      typename Array::value_type>::value), "");
		static_assert((hamon::is_same<typename Traits::reference,       typename Array::const_reference>::value), "");
		static_assert((hamon::is_same<typename Traits::pointer,         typename Array::const_pointer>::value), "");
		static_assert((hamon::is_same<typename Traits::difference_type, typename Array::difference_type>::value), "");
	}

	static_assert( hamon::contiguous_iterator_t<Iterator>::value, "");
	static_assert( hamon::indirectly_writable_t<Iterator, T>::value, "");
	static_assert( hamon::sentinel_for_t<Iterator, Iterator>::value, "");
	static_assert( hamon::sentinel_for_t<Iterator, ConstIterator>::value, "");
	static_assert(!hamon::sentinel_for_t<Iterator, ReverseIterator>::value, "");
	static_assert(!hamon::sentinel_for_t<Iterator, ConstReverseIterator>::value, "");
	static_assert( hamon::sized_sentinel_for_t<Iterator, Iterator>::value, "");
	static_assert( hamon::sized_sentinel_for_t<Iterator, ConstIterator>::value, "");
	static_assert(!hamon::sized_sentinel_for_t<Iterator, ReverseIterator>::value, "");
	static_assert(!hamon::sized_sentinel_for_t<Iterator, ConstReverseIterator>::value, "");
	static_assert( hamon::indirectly_movable_t<Iterator, Iterator>::value, "");
	static_assert(!hamon::indirectly_movable_t<Iterator, ConstIterator>::value, "");
	static_assert( hamon::indirectly_movable_t<Iterator, ReverseIterator>::value, "");
	static_assert(!hamon::indirectly_movable_t<Iterator, ConstReverseIterator>::value, "");
	static_assert( hamon::indirectly_movable_storable_t<Iterator, Iterator>::value, "");
	static_assert(!hamon::indirectly_movable_storable_t<Iterator, ConstIterator>::value, "");
	static_assert( hamon::indirectly_movable_storable_t<Iterator, ReverseIterator>::value, "");
	static_assert(!hamon::indirectly_movable_storable_t<Iterator, ConstReverseIterator>::value, "");
	static_assert( hamon::indirectly_copyable_t<Iterator, Iterator>::value, "");
	static_assert(!hamon::indirectly_copyable_t<Iterator, ConstIterator>::value, "");
	static_assert( hamon::indirectly_copyable_t<Iterator, ReverseIterator>::value, "");
	static_assert(!hamon::indirectly_copyable_t<Iterator, ConstReverseIterator>::value, "");
	static_assert( hamon::indirectly_copyable_storable_t<Iterator, Iterator>::value, "");
	static_assert(!hamon::indirectly_copyable_storable_t<Iterator, ConstIterator>::value, "");
	static_assert( hamon::indirectly_copyable_storable_t<Iterator, ReverseIterator>::value, "");
	static_assert(!hamon::indirectly_copyable_storable_t<Iterator, ConstReverseIterator>::value, "");
	static_assert( hamon::indirectly_swappable_t<Iterator, Iterator>::value, "");
	static_assert(!hamon::indirectly_swappable_t<Iterator, ConstIterator>::value, "");
	static_assert( hamon::indirectly_swappable_t<Iterator, ReverseIterator>::value, "");
	static_assert(!hamon::indirectly_swappable_t<Iterator, ConstReverseIterator>::value, "");

	static_assert( hamon::contiguous_iterator_t<ConstIterator>::value, "");
	static_assert(!hamon::indirectly_writable_t<ConstIterator, T>::value, "");
	static_assert( hamon::sentinel_for_t<ConstIterator, Iterator>::value, "");
	static_assert( hamon::sentinel_for_t<ConstIterator, ConstIterator>::value, "");
	static_assert(!hamon::sentinel_for_t<ConstIterator, ReverseIterator>::value, "");
	static_assert(!hamon::sentinel_for_t<ConstIterator, ConstReverseIterator>::value, "");
	static_assert( hamon::sized_sentinel_for_t<ConstIterator, Iterator>::value, "");
	static_assert( hamon::sized_sentinel_for_t<ConstIterator, ConstIterator>::value, "");
	static_assert(!hamon::sized_sentinel_for_t<ConstIterator, ReverseIterator>::value, "");
	static_assert(!hamon::sized_sentinel_for_t<ConstIterator, ConstReverseIterator>::value, "");
	static_assert( hamon::indirectly_movable_t<ConstIterator, Iterator>::value, "");
	static_assert(!hamon::indirectly_movable_t<ConstIterator, ConstIterator>::value, "");
	static_assert( hamon::indirectly_movable_t<ConstIterator, ReverseIterator>::value, "");
	static_assert(!hamon::indirectly_movable_t<ConstIterator, ConstReverseIterator>::value, "");
	static_assert( hamon::indirectly_movable_storable_t<ConstIterator, Iterator>::value, "");
	static_assert(!hamon::indirectly_movable_storable_t<ConstIterator, ConstIterator>::value, "");
	static_assert( hamon::indirectly_movable_storable_t<ConstIterator, ReverseIterator>::value, "");
	static_assert(!hamon::indirectly_movable_storable_t<ConstIterator, ConstReverseIterator>::value, "");
	static_assert( hamon::indirectly_copyable_t<ConstIterator, Iterator>::value, "");
	static_assert(!hamon::indirectly_copyable_t<ConstIterator, ConstIterator>::value, "");
	static_assert( hamon::indirectly_copyable_t<ConstIterator, ReverseIterator>::value, "");
	static_assert(!hamon::indirectly_copyable_t<ConstIterator, ConstReverseIterator>::value, "");
	static_assert( hamon::indirectly_copyable_storable_t<ConstIterator, Iterator>::value, "");
	static_assert(!hamon::indirectly_copyable_storable_t<ConstIterator, ConstIterator>::value, "");
	static_assert( hamon::indirectly_copyable_storable_t<ConstIterator, ReverseIterator>::value, "");
	static_assert(!hamon::indirectly_copyable_storable_t<ConstIterator, ConstReverseIterator>::value, "");
	static_assert(!hamon::indirectly_swappable_t<ConstIterator, Iterator>::value, "");
	static_assert(!hamon::indirectly_swappable_t<ConstIterator, ConstIterator>::value, "");
	static_assert(!hamon::indirectly_swappable_t<ConstIterator, ReverseIterator>::value, "");
	static_assert(!hamon::indirectly_swappable_t<ConstIterator, ConstReverseIterator>::value, "");
}

GTEST_TEST(ArrayTest, IteratorTest)
{
	IteratorTest<char, 0>();
	IteratorTest<char, 1>();
	IteratorTest<int, 0>();
	IteratorTest<int, 2>();
	IteratorTest<float, 0>();
	IteratorTest<float, 10>();
	IteratorTest<double, 0>();
	IteratorTest<double, 20>();
}

}	// namespace iterator_test

}	// namespace hamon_array_test
