/**
 *	@file	unit_test_set_lower_bound_heterogeneous.cpp
 *
 *	@brief	lower_bound のテスト
 *
 *	template<class K> iterator       lower_bound(const K& x);
 *	template<class K> const_iterator lower_bound(const K& x) const;
 */

#include <hamon/set/set.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_SET) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)

namespace hamon_set_test
{

namespace lower_bound_heterogeneous_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

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

// template<class K> iterator lower_bound(const K& x);
SET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::set<S, hamon::less<>>;
	using Iterator = typename Set::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().lower_bound(hamon::declval<int const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().lower_bound(hamon::declval<int const&>())), "");

	Set v;

	VERIFY(v.lower_bound(0) == v.end());
	VERIFY(v.lower_bound(1) == v.end());
	VERIFY(v.lower_bound(2) == v.end());
	VERIFY(v.lower_bound(3) == v.end());

	v.emplace(S{0});

	VERIFY(v.lower_bound(0) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(1) == v.end());
	VERIFY(v.lower_bound(2) == v.end());
	VERIFY(v.lower_bound(3) == v.end());

	v.emplace(S{2});

	VERIFY(v.lower_bound(0) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(1) == hamon::next(v.begin(), 1));
	VERIFY(v.lower_bound(2) == hamon::next(v.begin(), 1));
	VERIFY(v.lower_bound(3) == v.end());

	v.emplace(S{1});

	VERIFY(v.lower_bound(0) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(1) == hamon::next(v.begin(), 1));
	VERIFY(v.lower_bound(2) == hamon::next(v.begin(), 2));
	VERIFY(v.lower_bound(3) == v.end());

	return true;
}

// template<class K> const_iterator lower_bound(const K& x) const;
SET_TEST_CONSTEXPR bool test2()
{
	using Set = hamon::set<S, hamon::less<>>;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().lower_bound(hamon::declval<int const&>())), ConstIterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().lower_bound(hamon::declval<int const&>())), "");

	Set const v {S{5}, S{0}, S{4}, S{1}, S{5}, S{5}, S{1}};

	VERIFY(v.lower_bound(0) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(1) == hamon::next(v.begin(), 1));
	VERIFY(v.lower_bound(2) == hamon::next(v.begin(), 2));
	VERIFY(v.lower_bound(3) == hamon::next(v.begin(), 2));
	VERIFY(v.lower_bound(4) == hamon::next(v.begin(), 2));
	VERIFY(v.lower_bound(5) == hamon::next(v.begin(), 3));
	VERIFY(v.lower_bound(6) == v.end());

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, LowerBoundHeterogeneousTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test2());
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace lower_bound_heterogeneous_test

}	// namespace hamon_set_test

#endif
