/**
 *	@file	unit_test_set_find.cpp
 *
 *	@brief	find のテスト
 *
 *	iterator       find(const key_type& x);
 *	const_iterator find(const key_type& x) const;
 */

#include <hamon/set/set.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace find_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// iterator find(const key_type& x);
template <typename Key>
SET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::set<Key>;
	using Iterator = typename Set::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().find(hamon::declval<Key const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().find(hamon::declval<Key const&>())), "");

	Set v;

	VERIFY(v.find(Key{0}) == v.end());
	VERIFY(v.find(Key{1}) == v.end());
	VERIFY(v.find(Key{2}) == v.end());
	VERIFY(v.find(Key{3}) == v.end());

	v.emplace(Key{1});

	VERIFY(v.find(Key{0}) == v.end());
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{2}) == v.end());
	VERIFY(v.find(Key{3}) == v.end());

	v.emplace(Key{2});

	VERIFY(v.find(Key{0}) == v.end());
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{2}) == hamon::next(v.begin(), 1));
	VERIFY(v.find(Key{3}) == v.end());

	v.emplace(Key{0});

	VERIFY(v.find(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 1));
	VERIFY(v.find(Key{2}) == hamon::next(v.begin(), 2));
	VERIFY(v.find(Key{3}) == v.end());

	return true;
}

// const_iterator find(const key_type& x) const;
template <typename Key>
SET_TEST_CONSTEXPR bool test2()
{
	using Set = hamon::set<Key>;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), ConstIterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), "");

	Set const v {Key{3}, Key{1}, Key{1}, Key{3}, Key{1}, Key{4}};

	VERIFY(v.find(Key{0}) == v.end());
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{2}) == v.end());
	VERIFY(v.find(Key{3}) == hamon::next(v.begin(), 1));
	VERIFY(v.find(Key{4}) == hamon::next(v.begin(), 2));
	VERIFY(v.find(Key{5}) == v.end());

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, FindTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	SET_TEST_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test2<float>()));

	// https://en.cppreference.com/w/cpp/container/set/find
	{
		hamon::set<int> example{1, 2, 3, 4};
		auto search = example.find(2);
		EXPECT_TRUE(search != example.end());
		EXPECT_EQ(2, *search);
	}
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace find_test

}	// namespace hamon_set_test
