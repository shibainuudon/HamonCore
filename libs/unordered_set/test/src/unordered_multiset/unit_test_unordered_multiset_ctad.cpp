/**
 *	@file	unit_test_unordered_multiset_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class InputIterator,
 *		class Hash = hash<iter-key-type<InputIterator>>,
 *		class Pred = equal_to<iter-key-type<InputIterator>>,
 *		class Allocator = allocator<iter-to-alloc-type<InputIterator>>>
 *	unordered_multiset(InputIterator, InputIterator, typename see below::size_type = see below,
 *		Hash = Hash(), Pred = Pred(), Allocator = Allocator())
 *	-> unordered_multiset<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, Hash, Pred, Allocator>;
 *
 *	template<ranges::input_range R, class Hash = hash<range-key-type<R>>,
 *		class Pred = equal_to<range-key-type<R>>,
 *		class Allocator = allocator<range-to-alloc-type<R>>>
 *	unordered_multiset(from_range_t, R&&, typename see below::size_type = see below,
 *		Hash = Hash(), Pred = Pred(), Allocator = Allocator())
 *	-> unordered_multiset<range-key-type<R>, range-mapped-type<R>, Hash, Pred, Allocator>;
 *
 *	template<class Key, class T, class Hash = hash<Key>,
 *		class Pred = equal_to<Key>, class Allocator = allocator<pair<const Key, T>>>
 *	unordered_multiset(initializer_list<pair<Key, T>>,
 *		typename see below::size_type = see below, Hash = Hash(),
 *		Pred = Pred(), Allocator = Allocator())
 *	-> unordered_multiset<Key, T, Hash, Pred, Allocator>;
 *
 *	template<class InputIterator, class Allocator>
 *	unordered_multiset(InputIterator, InputIterator, typename see below::size_type, Allocator)
 *	-> unordered_multiset<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>,
 *		hash<iter-key-type<InputIterator>>,
 *		equal_to<iter-key-type<InputIterator>>, Allocator>;
 *
 *	template<class InputIterator, class Allocator>
 *	unordered_multiset(InputIterator, InputIterator, Allocator)
 *	-> unordered_multiset<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>,
 *		hash<iter-key-type<InputIterator>>,
 *		equal_to<iter-key-type<InputIterator>>, Allocator>;
 *
 *	template<class InputIterator, class Hash, class Allocator>
 *	unordered_multiset(InputIterator, InputIterator, typename see below::size_type, Hash, Allocator)
 *	-> unordered_multiset<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, Hash,
 *		equal_to<iter-key-type<InputIterator>>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	unordered_multiset(from_range_t, R&&, typename see below::size_type, Allocator)
 *	-> unordered_multiset<range-key-type<R>, range-mapped-type<R>, hash<range-key-type<R>>,
 *		equal_to<range-key-type<R>>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	unordered_multiset(from_range_t, R&&, Allocator)
 *	-> unordered_multiset<range-key-type<R>, range-mapped-type<R>, hash<range-key-type<R>>,
 *		equal_to<range-key-type<R>>, Allocator>;
 *
 *	template<ranges::input_range R, class Hash, class Allocator>
 *	unordered_multiset(from_range_t, R&&, typename see below::size_type, Hash, Allocator)
 *	-> unordered_multiset<range-key-type<R>, range-mapped-type<R>, Hash,
 *		equal_to<range-key-type<R>>, Allocator>;
 *
 *	template<class Key, class T, class Allocator>
 *	unordered_multiset(initializer_list<pair<Key, T>>, typename see below::size_type, Allocator)
 *	-> unordered_multiset<Key, T, hash<Key>, equal_to<Key>, Allocator>;
 *
 *	template<class Key, class T, class Allocator>
 *	unordered_multiset(initializer_list<pair<Key, T>>, Allocator)
 *	-> unordered_multiset<Key, T, hash<Key>, equal_to<Key>, Allocator>;
 *
 *	template<class Key, class T, class Hash, class Allocator>
 *	unordered_multiset(initializer_list<pair<Key, T>>, typename see below::size_type, Hash, Allocator)
 *	-> unordered_multiset<Key, T, Hash, equal_to<Key>, Allocator>;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"
#include "ranges_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace ctad_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test()
{
	// TODO
	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, CtadTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_unordered_multiset_test
