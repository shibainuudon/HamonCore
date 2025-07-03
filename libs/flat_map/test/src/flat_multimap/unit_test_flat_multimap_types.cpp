/**
 *	@file	unit_test_flat_multimap_types.cpp
 *
 *	@brief	types のテスト
 *
 *	using key_type               = Key;
 *	using mapped_type            = T;
 *	using value_type             = pair<key_type, mapped_type>;
 *	using key_compare            = Compare;
 *	using reference              = pair<const key_type&, mapped_type&>;
 *	using const_reference        = pair<const key_type&, const mapped_type&>;
 *	using size_type              = size_t;
 *	using difference_type        = ptrdiff_t;
 *	using iterator               = implementation-defined;     // see [container.requirements]
 *	using const_iterator         = implementation-defined;     // see [container.requirements]
 *	using reverse_iterator       = std::reverse_iterator<iterator>;
 *	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
 *	using key_container_type     = KeyContainer;
 *	using mapped_container_type  = MappedContainer;
 *
 *	class value_compare;
 *
 *	struct containers;
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace types_test
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
	using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;

	static_assert(hamon::is_same<typename Map::key_type, Key>::value, "");
	static_assert(hamon::is_same<typename Map::mapped_type, T>::value, "");
	static_assert(hamon::is_same<typename Map::value_type, hamon::pair<Key, T>>::value, "");
	static_assert(hamon::is_same<typename Map::key_compare, Compare>::value, "");
	static_assert(hamon::is_same<typename Map::reference, hamon::pair<Key const&, T&>>::value, "");
	static_assert(hamon::is_same<typename Map::const_reference, hamon::pair<Key const&, T const&>>::value, "");
	static_assert(hamon::is_same<typename Map::size_type, hamon::size_t>::value, "");
	static_assert(hamon::is_same<typename Map::difference_type, hamon::ptrdiff_t>::value, "");
	static_assert(hamon::random_access_iterator_t<typename Map::iterator>::value, "");
	static_assert(hamon::random_access_iterator_t<typename Map::const_iterator>::value, "");
	static_assert(hamon::is_same<typename Map::reverse_iterator, hamon::reverse_iterator<typename Map::iterator>>::value, "");
	static_assert(hamon::is_same<typename Map::const_reverse_iterator, hamon::reverse_iterator<typename Map::const_iterator>>::value, "");
	static_assert(hamon::is_same<typename Map::key_container_type, KeyContainer>::value, "");
	static_assert(hamon::is_same<typename Map::mapped_container_type, MappedContainer>::value, "");
	static_assert(hamon::is_object<typename Map::value_compare>::value, "");
	static_assert(hamon::is_object<typename Map::containers>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, TypesTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace types_test

}	// namespace hamon_flat_multimap_test
