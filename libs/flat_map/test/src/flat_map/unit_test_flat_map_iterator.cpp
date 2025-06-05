/**
 *	@file	unit_test_flat_map_iterator.cpp
 *
 *	@brief	iterator のテスト
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/concepts.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/utility.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace iterator_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>;
	using value_type      = typename Map::value_type;
	using reference       = typename Map::reference;
	using const_reference = typename Map::const_reference;
	using difference_type = typename Map::difference_type;
	using iterator        = typename Map::iterator;
	using const_iterator  = typename Map::const_iterator;

	static_assert( hamon::detail::cpp17_input_iterator_t<iterator>::value, "");
	static_assert(!hamon::detail::cpp17_forward_iterator_t<iterator>::value, "");
	static_assert(!hamon::detail::cpp17_bidirectional_iterator_t<iterator>::value, "");
	static_assert(!hamon::detail::cpp17_random_access_iterator_t<iterator>::value, "");
	static_assert( hamon::input_iterator_t<iterator>::value, "");
	static_assert( hamon::forward_iterator_t<iterator>::value, "");
	static_assert( hamon::bidirectional_iterator_t<iterator>::value, "");
	static_assert( hamon::random_access_iterator_t<iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<iterator>::value, "");
	static_assert(hamon::is_same<value_type, hamon::iter_value_t<iterator>>::value, "");
	static_assert(!hamon::is_same<value_type&, hamon::iter_reference_t<iterator>>::value, "");
	static_assert(hamon::is_same<reference, hamon::iter_reference_t<iterator>>::value, "");
	static_assert(hamon::is_same<difference_type, hamon::iter_difference_t<iterator>>::value, "");
	static_assert(hamon::is_default_constructible<iterator>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<iterator>::value, "");
	static_assert(!hamon::is_constructible<iterator, value_type*>::value, "");
	static_assert(!hamon::is_constructible<iterator, value_type const*>::value, "");
	static_assert(!hamon::is_same<value_type&, decltype(*hamon::declval<iterator const&>())>::value, "");
	static_assert(hamon::is_same<reference, decltype(*hamon::declval<iterator const&>())>::value, "");
	static_assert(!hamon::is_same<value_type*, decltype(hamon::declval<iterator const&>().operator->())>::value, "");
	static_assert(hamon::is_same<iterator&, decltype(++hamon::declval<iterator&>())>::value, "");
	static_assert(hamon::is_same<iterator,  decltype(hamon::declval<iterator&>()++)>::value, "");
	static_assert(hamon::is_same<iterator&, decltype(--hamon::declval<iterator&>())>::value, "");
	static_assert(hamon::is_same<iterator,  decltype(hamon::declval<iterator&>()--)>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() == (hamon::declval<iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<iterator const&>() != (hamon::declval<iterator const&>()))>::value, "");

	static_assert( hamon::detail::cpp17_input_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::detail::cpp17_forward_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::detail::cpp17_bidirectional_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::detail::cpp17_random_access_iterator_t<const_iterator>::value, "");
	static_assert( hamon::input_iterator_t<const_iterator>::value, "");
	static_assert( hamon::forward_iterator_t<const_iterator>::value, "");
	static_assert( hamon::bidirectional_iterator_t<const_iterator>::value, "");
	static_assert( hamon::random_access_iterator_t<const_iterator>::value, "");
	static_assert(!hamon::contiguous_iterator_t<const_iterator>::value, "");
	static_assert(hamon::is_same<value_type, hamon::iter_value_t<const_iterator>>::value, "");
	static_assert(!hamon::is_same<value_type&, hamon::iter_reference_t<const_iterator>>::value, "");
	static_assert(hamon::is_same<const_reference, hamon::iter_reference_t<const_iterator>>::value, "");
	static_assert(hamon::is_same<difference_type, hamon::iter_difference_t<const_iterator>>::value, "");
	static_assert(hamon::is_default_constructible<const_iterator>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<const_iterator>::value, "");
	static_assert(!hamon::is_constructible<const_iterator, value_type*>::value, "");
	static_assert(!hamon::is_constructible<const_iterator, value_type const*>::value, "");
	static_assert(!hamon::is_same<value_type&, decltype(*hamon::declval<const_iterator const&>())>::value, "");
	static_assert(hamon::is_same<const_reference, decltype(*hamon::declval<const_iterator const&>())>::value, "");
	static_assert(!hamon::is_same<value_type*, decltype(hamon::declval<const_iterator const&>().operator->())>::value, "");
	static_assert(hamon::is_same<const_iterator&, decltype(++hamon::declval<const_iterator&>())>::value, "");
	static_assert(hamon::is_same<const_iterator,  decltype(hamon::declval<const_iterator&>()++)>::value, "");
	static_assert(hamon::is_same<const_iterator&, decltype(--hamon::declval<const_iterator&>())>::value, "");
	static_assert(hamon::is_same<const_iterator,  decltype(hamon::declval<const_iterator&>()--)>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() == (hamon::declval<const_iterator const&>()))>::value, "");
	static_assert(hamon::is_same<bool, decltype(hamon::declval<const_iterator const&>() != (hamon::declval<const_iterator const&>()))>::value, "");

	static_assert( hamon::is_constructible<iterator,       iterator>::value, "");
	static_assert(!hamon::is_constructible<iterator,       const_iterator>::value, "");
	static_assert( hamon::is_constructible<const_iterator, iterator>::value, "");
	static_assert( hamon::is_constructible<const_iterator, const_iterator>::value, "");

	// TODO

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, IteratorTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace iterator_test

}	// namespace hamon_flat_map_test
