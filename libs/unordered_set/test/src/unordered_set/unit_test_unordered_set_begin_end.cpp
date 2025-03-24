/**
 *	@file	unit_test_unordered_set_begin_end.cpp
 *
 *	@brief	begin, end のテスト
 *
 *	constexpr iterator       begin() noexcept;
 *	constexpr const_iterator begin() const noexcept;
 *	constexpr iterator       end() noexcept;
 *	constexpr const_iterator end() const noexcept;
 *	constexpr const_iterator cbegin() const noexcept;
 *	constexpr const_iterator cend() const noexcept;
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace begin_end_test
{

#if !defined(HAMON_USE_STD_UNORDERED_SET)
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::unordered_set<Key>;
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().begin()),   Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().end()),     Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().cbegin()),  ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().cend()),    ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().begin()),  ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().end()),    ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().cbegin()), ConstIterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().cend()),   ConstIterator>::value, "");

	static_assert(noexcept(hamon::declval<Set&>().begin()), "");
	static_assert(noexcept(hamon::declval<Set&>().end()), "");
	static_assert(noexcept(hamon::declval<Set&>().cbegin()), "");
	static_assert(noexcept(hamon::declval<Set&>().cend()), "");
	static_assert(noexcept(hamon::declval<Set const&>().begin()), "");
	static_assert(noexcept(hamon::declval<Set const&>().end()), "");
	static_assert(noexcept(hamon::declval<Set const&>().cbegin()), "");
	static_assert(noexcept(hamon::declval<Set const&>().cend()), "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, BeginEndTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace begin_end_test

}	// namespace hamon_unordered_set_test
