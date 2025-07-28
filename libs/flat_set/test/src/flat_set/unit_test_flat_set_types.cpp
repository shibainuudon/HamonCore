/**
 *	@file	unit_test_flat_set_types.cpp
 *
 *	@brief	types のテスト
 *
 *	using key_type                  = Key;
 *	using value_type                = Key;
 *	using key_compare               = Compare;
 *	using value_compare             = Compare;
 *	using reference                 = value_type&;
 *	using const_reference           = const value_type&;
 *	using size_type                 = typename KeyContainer::size_type;
 *	using difference_type           = typename KeyContainer::difference_type;
 *	using iterator                  = implementation-defined;  // see [container.requirements]
 *	using const_iterator            = implementation-defined;  // see [container.requirements]
 *	using reverse_iterator          = std::reverse_iterator<iterator>;
 *	using const_reverse_iterator    = std::reverse_iterator<const_iterator>;
 *	using container_type            = KeyContainer;
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace types_test
{

template <typename KeyContainer, typename Compare>
void test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_set<Key, Compare, KeyContainer>;

	static_assert(hamon::is_same<typename Set::key_type, Key>::value, "");
	static_assert(hamon::is_same<typename Set::value_type, Key>::value, "");
	static_assert(hamon::is_same<typename Set::key_compare, Compare>::value, "");
	static_assert(hamon::is_same<typename Set::value_compare, Compare>::value, "");
	static_assert(hamon::is_same<typename Set::reference, Key&>::value, "");
	static_assert(hamon::is_same<typename Set::const_reference, const Key&>::value, "");
	static_assert(hamon::is_same<typename Set::size_type, typename KeyContainer::size_type>::value, "");
	static_assert(hamon::is_same<typename Set::difference_type, typename KeyContainer::difference_type>::value, "");
	static_assert(hamon::random_access_iterator_t<typename Set::iterator>::value, "");
	static_assert(hamon::random_access_iterator_t<typename Set::const_iterator>::value, "");
	static_assert(hamon::is_same<typename Set::reverse_iterator, hamon::reverse_iterator<typename Set::iterator>>::value, "");
	static_assert(hamon::is_same<typename Set::const_reverse_iterator, hamon::reverse_iterator<typename Set::const_iterator>>::value, "");
	static_assert(hamon::is_same<typename Set::container_type, KeyContainer>::value, "");
}

GTEST_TEST(FlatSetTest, TypesTest)
{
	test<hamon::vector<int>, hamon::less<int>>();
	test<hamon::deque<double>, hamon::greater<double>>();
	test<MinSequenceContainer<char>, hamon::less<int>>();
}

}	// namespace types_test

}	// namespace hamon_flat_set_test
