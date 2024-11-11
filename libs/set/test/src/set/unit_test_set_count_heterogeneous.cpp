/**
 *	@file	unit_test_set_count_heterogeneous.cpp
 *
 *	@brief	count のテスト
 *
 *	template<class K> size_type count(const K& x) const;
 */

#include <hamon/set/set.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_SET) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)

namespace hamon_set_test
{

namespace count_heterogeneous_test
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

struct R
{
	static int s_ctor_count;

	int value;

	R(int v) : value(v)
	{
		++s_ctor_count;
	}

	friend bool operator<(R const& lhs, R const& rhs)
	{
		return lhs.value < rhs.value;
	}

	friend bool operator<(R const& lhs, int rhs)
	{
		return lhs.value < rhs;
	}

	friend bool operator<(int lhs, R const& rhs)
	{
		return lhs < rhs.value;
	}
};

int R::s_ctor_count = 0;

// template<class K> size_type count(const K& x) const;
SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::set<S, hamon::less<>>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().count(hamon::declval<int const&>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().count(hamon::declval<int const&>())), "");

	Set const v {S{0}, S{1}, S{4}, S{5}, S{1}, S{5}, S{5}};

	VERIFY(v.count(0) == 1);
	VERIFY(v.count(1) == 1);
	VERIFY(v.count(2) == 0);
	VERIFY(v.count(3) == 0);
	VERIFY(v.count(4) == 1);
	VERIFY(v.count(5) == 1);
	VERIFY(v.count(6) == 0);

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, CountHeterogeneousTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test());

	// https://en.cppreference.com/w/cpp/container/set/count

	R::s_ctor_count = 0;
	{
		hamon::set<R, hamon::less<>> r{3, 1, 4, 1, 5};
		EXPECT_EQ(5, R::s_ctor_count);
		EXPECT_EQ(1u, r.count(1));
		EXPECT_EQ(5, R::s_ctor_count);
		EXPECT_EQ(0u, r.count(2));
		EXPECT_EQ(5, R::s_ctor_count);
	}
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace count_heterogeneous_test

}	// namespace hamon_set_test

#endif
