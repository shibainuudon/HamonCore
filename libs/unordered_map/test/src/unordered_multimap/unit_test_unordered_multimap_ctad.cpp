/**
 *	@file	unit_test_unordered_multimap_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class InputIterator,
 *		class Hash = hash<iter-key-type<InputIterator>>,
 *		class Pred = equal_to<iter-key-type<InputIterator>>,
 *		class Allocator = allocator<iter-to-alloc-type<InputIterator>>>
 *	unordered_multimap(InputIterator, InputIterator, typename see below::size_type = see below,
 *		Hash = Hash(), Pred = Pred(), Allocator = Allocator())
 *	-> unordered_multimap<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, Hash, Pred, Allocator>;
 *
 *	template<ranges::input_range R, class Hash = hash<range-key-type<R>>,
 *		class Pred = equal_to<range-key-type<R>>,
 *		class Allocator = allocator<range-to-alloc-type<R>>>
 *	unordered_multimap(from_range_t, R&&, typename see below::size_type = see below,
 *		Hash = Hash(), Pred = Pred(), Allocator = Allocator())
 *	-> unordered_multimap<range-key-type<R>, range-mapped-type<R>, Hash, Pred, Allocator>;
 *
 *	template<class Key, class T, class Hash = hash<Key>,
 *		class Pred = equal_to<Key>, class Allocator = allocator<pair<const Key, T>>>
 *	unordered_multimap(initializer_list<pair<Key, T>>,
 *		typename see below::size_type = see below, Hash = Hash(),
 *		Pred = Pred(), Allocator = Allocator())
 *	-> unordered_multimap<Key, T, Hash, Pred, Allocator>;
 *
 *	template<class InputIterator, class Allocator>
 *	unordered_multimap(InputIterator, InputIterator, typename see below::size_type, Allocator)
 *	-> unordered_multimap<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>,
 *		hash<iter-key-type<InputIterator>>,
 *		equal_to<iter-key-type<InputIterator>>, Allocator>;
 *
 *	template<class InputIterator, class Allocator>
 *	unordered_multimap(InputIterator, InputIterator, Allocator)
 *	-> unordered_multimap<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>,
 *		hash<iter-key-type<InputIterator>>,
 *		equal_to<iter-key-type<InputIterator>>, Allocator>;
 *
 *	template<class InputIterator, class Hash, class Allocator>
 *	unordered_multimap(InputIterator, InputIterator, typename see below::size_type, Hash, Allocator)
 *	-> unordered_multimap<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, Hash,
 *		equal_to<iter-key-type<InputIterator>>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	unordered_multimap(from_range_t, R&&, typename see below::size_type, Allocator)
 *	-> unordered_multimap<range-key-type<R>, range-mapped-type<R>, hash<range-key-type<R>>,
 *		equal_to<range-key-type<R>>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	unordered_multimap(from_range_t, R&&, Allocator)
 *	-> unordered_multimap<range-key-type<R>, range-mapped-type<R>, hash<range-key-type<R>>,
 *		equal_to<range-key-type<R>>, Allocator>;
 *
 *	template<ranges::input_range R, class Hash, class Allocator>
 *	unordered_multimap(from_range_t, R&&, typename see below::size_type, Hash, Allocator)
 *	-> unordered_multimap<range-key-type<R>, range-mapped-type<R>, Hash,
 *		equal_to<range-key-type<R>>, Allocator>;
 *
 *	template<class Key, class T, class Allocator>
 *	unordered_multimap(initializer_list<pair<Key, T>>, typename see below::size_type, Allocator)
 *	-> unordered_multimap<Key, T, hash<Key>, equal_to<Key>, Allocator>;
 *
 *	template<class Key, class T, class Allocator>
 *	unordered_multimap(initializer_list<pair<Key, T>>, Allocator)
 *	-> unordered_multimap<Key, T, hash<Key>, equal_to<Key>, Allocator>;
 *
 *	template<class Key, class T, class Hash, class Allocator>
 *	unordered_multimap(initializer_list<pair<Key, T>>, typename see below::size_type, Hash, Allocator)
 *	-> unordered_multimap<Key, T, Hash, equal_to<Key>, Allocator>;
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "ranges_test.hpp"

namespace hamon_unordered_multimap_test
{

namespace ctad_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	// TODO
	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, CtadTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_unordered_multimap_test
