/**
 *	@file	unit_test_flat_map_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class KeyContainer, class MappedContainer, class Compare = less<typename KeyContainer::value_type>>
 *	flat_map(KeyContainer, MappedContainer, Compare = Compare())
 *	-> flat_map<typename KeyContainer::value_type, typename MappedContainer::value_type, Compare, KeyContainer, MappedContainer>;
 *
 *	template<class KeyContainer, class MappedContainer, class Allocator>
 *	flat_map(KeyContainer, MappedContainer, Allocator)
 *	-> flat_map<typename KeyContainer::value_type, typename MappedContainer::value_type, less<typename KeyContainer::value_type>, KeyContainer, MappedContainer>;
 *
 *	template<class KeyContainer, class MappedContainer, class Compare, class Allocator>
 *	flat_map(KeyContainer, MappedContainer, Compare, Allocator)
 *	-> flat_map<typename KeyContainer::value_type, typename MappedContainer::value_type, Compare, KeyContainer, MappedContainer>;
 *
 *	template<class KeyContainer, class MappedContainer, class Compare = less<typename KeyContainer::value_type>>
 *	flat_map(sorted_unique_t, KeyContainer, MappedContainer, Compare = Compare())
 *	-> flat_map<typename KeyContainer::value_type, typename MappedContainer::value_type, Compare, KeyContainer, MappedContainer>;
 *
 *	template<class KeyContainer, class MappedContainer, class Allocator>
 *	flat_map(sorted_unique_t, KeyContainer, MappedContainer, Allocator)
 *	-> flat_map<typename KeyContainer::value_type, typename MappedContainer::value_type, less<typename KeyContainer::value_type>, KeyContainer, MappedContainer>;
 *
 *	template<class KeyContainer, class MappedContainer, class Compare, class Allocator>
 *	flat_map(sorted_unique_t, KeyContainer, MappedContainer, Compare, Allocator)
 *	-> flat_map<typename KeyContainer::value_type, typename MappedContainer::value_type, Compare, KeyContainer, MappedContainer>;
 *
 *	template<class InputIterator, class Compare = less<iter-key-type<InputIterator>>>
 *	flat_map(InputIterator, InputIterator, Compare = Compare())
 *	-> flat_map<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, Compare>;
 *
 *	template<class InputIterator, class Compare = less<iter-key-type<InputIterator>>>
 *	flat_map(sorted_unique_t, InputIterator, InputIterator, Compare = Compare())
 *	-> flat_map<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, Compare>;
 *
 *	template<ranges::input_range R, class Compare = less<range-key-type<R>>, class Allocator = allocator<byte>>
 *	flat_map(from_range_t, R&&, Compare = Compare(), Allocator = Allocator())
 *	-> flat_map<range-key-type<R>, range-mapped-type<R>, Compare, vector<range-key-type<R>, alloc-rebind<Allocator, range-key-type<R>>>, vector<range-mapped-type<R>, alloc-rebind<Allocator, range-mapped-type<R>>>>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	flat_map(from_range_t, R&&, Allocator)
 *	-> flat_map<range-key-type<R>, range-mapped-type<R>, less<range-key-type<R>>, vector<range-key-type<R>, alloc-rebind<Allocator, range-key-type<R>>>, vector<range-mapped-type<R>, alloc-rebind<Allocator, range-mapped-type<R>>>>;
 *
 *	template<class Key, class T, class Compare = less<Key>>
 *	flat_map(initializer_list<pair<Key, T>>, Compare = Compare())
 *	-> flat_map<Key, T, Compare>;
 *
 *	template<class Key, class T, class Compare = less<Key>>
 *	flat_map(sorted_unique_t, initializer_list<pair<Key, T>>, Compare = Compare())
 *	-> flat_map<Key, T, Compare>;
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace ctad_test
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

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, CtadTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_flat_map_test
