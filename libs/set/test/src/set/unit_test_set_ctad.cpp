/**
 *	@file	unit_test_set_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class InputIterator,
 *		class Compare = less<iter-value-type<InputIterator>>,
 *		class Allocator = allocator<iter-value-type<InputIterator>>>
 *	set(InputIterator, InputIterator, Compare = Compare(), Allocator = Allocator())
 *		-> set<iter-value-type<InputIterator>, Compare, Allocator>;
 *
 *	template<ranges::input_range R, class Compare = less<ranges::range_value_t<R>>,
 *		class Allocator = allocator<ranges::range_value_t<R>>>
 *	set(from_range_t, R&&, Compare = Compare(), Allocator = Allocator())
 *		-> set<ranges::range_value_t<R>, Compare, Allocator>;
 *
 *	template<class Key, class Compare = less<Key>, class Allocator = allocator<Key>>
 *	set(initializer_list<Key>, Compare = Compare(), Allocator = Allocator())
 *		-> set<Key, Compare, Allocator>;
 *
 *	template<class InputIterator, class Allocator>
 *	set(InputIterator, InputIterator, Allocator)
 *		-> set<iter-value-type<InputIterator>, less<iter-value-type<InputIterator>>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	set(from_range_t, R&&, Allocator)
 *		-> set<ranges::range_value_t<R>, less<ranges::range_value_t<R>>, Allocator>;
 *
 *	template<class Key, class Allocator>
 *	set(initializer_list<Key>, Allocator) -> set<Key, less<Key>, Allocator>;
 */

#include <hamon/set/set.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace ctad_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
SET_TEST_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, CtadTest)
{
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_set_test
