/**
 *	@file	unit_test_set_insert_position_heterogeneous.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class K> iterator insert(const_iterator position, K&& x);
 */

#include <hamon/set/set.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_SET) || \
	(defined(__cpp_lib_associative_heterogeneous_insertion) && (__cpp_lib_associative_heterogeneous_insertion >= 202306L))

namespace hamon_set_test
{

namespace insert_position_heterogeneous_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

struct S
{
	int value;

	constexpr explicit S(int v) : value(v) {}

	friend constexpr bool operator<(S const& lhs, S const& rhs)
	{
		return lhs.value < rhs.value;
	}

	friend constexpr bool operator<(S const& lhs, int rhs)
	{
		return lhs.value < rhs;
	}

	friend constexpr bool operator<(int lhs, S const& rhs)
	{
		return lhs < rhs.value;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::set<S, hamon::less<>>;
	using ConstIterator = typename Set::const_iterator;
	using Iterator = typename Set::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::declval<ConstIterator>(), hamon::declval<int>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().insert(hamon::declval<ConstIterator>(), hamon::declval<int>())), "");

	Set v;

	{
		auto r = v.insert(v.end(), 10);
		VERIFY(r == v.begin());

		VERIFY(v.size() == 1);
		auto it = v.begin();
		VERIFY(it->value == 10);
		++it;
		VERIFY(it == v.end());
	}

	{
		auto r = v.insert(v.end(), 20);
		VERIFY(r == hamon::next(v.begin(), 1));

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(it->value == 10);
		++it;
		VERIFY(it->value == 20);
		++it;
		VERIFY(it == v.end());
	}

	{
		auto r = v.insert(v.end(), 10);
		VERIFY(r == hamon::next(v.begin(), 0));

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(it->value == 10);
		++it;
		VERIFY(it->value == 20);
		++it;
		VERIFY(it == v.end());
	}

	{
		auto r = v.insert(v.begin(), 30);
		VERIFY(r == hamon::next(v.begin(), 2));

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(it->value == 10);
		++it;
		VERIFY(it->value == 20);
		++it;
		VERIFY(it->value == 30);
		++it;
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, InsertPositionHeterogeneousTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace insert_position_heterogeneous_test

}	// namespace hamon_set_test

#endif
