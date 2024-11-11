/**
 *	@file	unit_test_map_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class InputIterator, class Compare = less<iter-key-type<InputIterator>>,
 *		class Allocator = allocator<iter-to-alloc-type<InputIterator>>>
 *	map(InputIterator, InputIterator, Compare = Compare(), Allocator = Allocator())
 *		-> map<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>, Compare, Allocator>;
 *
 *	template<ranges::input_range R, class Compare = less<range-key-type<R>,
 *		class Allocator = allocator<range-to-alloc-type<R>>>
 *	map(from_range_t, R&&, Compare = Compare(), Allocator = Allocator())
 *		-> map<range-key-type<R>, range-mapped-type<R>, Compare, Allocator>;
 *
 *	template<class Key, class T, class Compare = less<Key>,
 *		class Allocator = allocator<pair<const Key, T>>>
 *	map(initializer_list<pair<Key, T>>, Compare = Compare(), Allocator = Allocator())
 *		-> map<Key, T, Compare, Allocator>;
 *
 *	template<class InputIterator, class Allocator>
 *	map(InputIterator, InputIterator, Allocator)
 *		-> map<iter-key-type<InputIterator>, iter-mapped-type<InputIterator>,
 *			less<iter-key-type<InputIterator>>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	map(from_range_t, R&&, Allocator)
 *		-> map<range-key-type<R>, range-mapped-type<R>, less<range-key-type<R>>, Allocator>;
 *
 *	template<class Key, class T, class Allocator>
 *	map(initializer_list<pair<Key, T>>, Allocator) -> map<Key, T, less<Key>, Allocator>;
 */

#include <hamon/map/map.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace ctad_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, CtadTest)
{
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_map_test
