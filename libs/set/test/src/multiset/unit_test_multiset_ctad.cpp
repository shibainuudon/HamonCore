/**
 *	@file	unit_test_multiset_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class InputIterator,
 *		class Compare = less<iter-value-type<InputIterator>>,
 *		class Allocator = allocator<iter-value-type<InputIterator>>>
 *	multiset(InputIterator, InputIterator, Compare = Compare(), Allocator = Allocator())
 *		-> multiset<iter-value-type<InputIterator>, Compare, Allocator>;
 *
 *	template<ranges::input_range R, class Compare = less<ranges::range_value_t<R>>,
 *		class Allocator = allocator<ranges::range_value_t<R>>>
 *	multiset(from_range_t, R&&, Compare = Compare(), Allocator = Allocator())
 *		-> multiset<ranges::range_value_t<R>, Compare, Allocator>;
 *
 *	template<class Key, class Compare = less<Key>, class Allocator = allocator<Key>>
 *	multiset(initializer_list<Key>, Compare = Compare(), Allocator = Allocator())
 *		-> multiset<Key, Compare, Allocator>;
 *
 *	template<class InputIterator, class Allocator>
 *	multiset(InputIterator, InputIterator, Allocator)
 *		-> multiset<iter-value-type<InputIterator>, less<iter-value-type<InputIterator>>, Allocator>;
 *
 *	template<ranges::input_range R, class Allocator>
 *	multiset(from_range_t, R&&, Allocator)
 *		-> multiset<ranges::range_value_t<R>, less<ranges::range_value_t<R>>, Allocator>;
 *
 *	template<class Key, class Allocator>
 *	multiset(initializer_list<Key>, Allocator) -> multiset<Key, less<Key>, Allocator>;
 */

#include <hamon/set/multiset.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace ctad_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
MULTISET_TEST_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, CtadTest)
{
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace ctad_test

}	// namespace hamon_multiset_test
