/**
 *	@file	unit_test_set_count.cpp
 *
 *	@brief	count のテスト
 *
 *	size_type count(const key_type& x) const;
 */

#include <hamon/set/set.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace count_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// size_type count(const key_type& x) const;
template <typename Key>
SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::set<Key>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().count(hamon::declval<Key const&>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().count(hamon::declval<Key const&>())), "");

	Set const v {Key{1}, Key{4}, Key{1}, Key{1}, Key{3}, Key{3}};

	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 1);
	VERIFY(v.count(Key{4}) == 1);
	VERIFY(v.count(Key{5}) == 0);

	return true;
}

#undef VERIFY

struct S
{
	static int s_ctor_count;

	int value;

	S(int v) : value(v)
	{
		++s_ctor_count;
	}

	friend bool operator<(S const& lhs, S const& rhs)
	{
		return lhs.value < rhs.value;
	}
};

int S::s_ctor_count = 0;

GTEST_TEST(SetTest, CountTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));

	// https://en.cppreference.com/w/cpp/container/set/count

	S::s_ctor_count = 0;
	{
		hamon::set<S> s{3, 1, 4, 1, 5};
		EXPECT_EQ(5, S::s_ctor_count);
		EXPECT_EQ(1u, s.count(1));
		EXPECT_EQ(6, S::s_ctor_count);
		EXPECT_EQ(0u, s.count(2));
		EXPECT_EQ(7, S::s_ctor_count);
	}
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace count_test

}	// namespace hamon_set_test
