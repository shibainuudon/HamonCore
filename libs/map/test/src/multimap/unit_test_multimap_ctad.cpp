/**
 *	@file	unit_test_multimap_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class InputIterator, class Compare = less<iter-key-type<InputIterator>>,
 *		class Allocator = allocator<iter-to-alloc-type<InputIterator>>>
 *	multimap(InputIterator, InputIterator, Compare = Compare(), Allocator = Allocator())
 *	-> multimap<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, Compare, Allocator>;
 *
 *	template<ranges::input_range R, class Compare = less<range-key-type<R>>,
 *		class Allocator = allocator<range-to-alloc-type<R>>>
 *	multimap(from_range_t, R&&, Compare = Compare(), Allocator = Allocator())
 *	-> multimap<range-key-type<R>, range-mapped-type<R>, Compare, Allocator>;
 *
 *	template<class Key, class T, class Compare = less<Key>,
 *		class Allocator = allocator<pair<const Key, T>>>
 *	multimap(initializer_list<pair<Key, T>>, Compare = Compare(), Allocator = Allocator())
 *	-> multimap<Key, T, Compare, Allocator>;
 *
 *	template<class InputIterator, class Allocator>
 *	multimap(InputIterator, InputIterator, Allocator)
 *	-> multimap<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, less<iter-key-type<InputIterator>>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	multimap(from_range_t, R&&, Allocator)
 *	-> multimap<range-key-type<R>, range-mapped-type<R>, less<range-key-type<R>>, Allocator>;
 *
 *	template<class Key, class T, class Allocator>
 *	multimap(initializer_list<pair<Key, T>>, Allocator)
 *	-> multimap<Key, T, less<Key>, Allocator>;
 */

#include <hamon/map/multimap.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace ctad_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(MultimapTest, CtadTest)
{
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_multimap_test
