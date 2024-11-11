/**
 *	@file	unit_test_multiset_count_heterogeneous.cpp
 *
 *	@brief	count のテスト
 *
 *	template<class K> size_type count(const K& x) const;
 */

#include <hamon/set/multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_MULTISET) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)

namespace hamon_multiset_test
{

namespace count_heterogeneous_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
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

// template<class K> size_type count(const K& x) const;
MULTISET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::multiset<S, hamon::less<>>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().count(hamon::declval<int const&>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().count(hamon::declval<int const&>())), "");

	Set const v {S{0}, S{1}, S{4}, S{5}, S{1}, S{5}, S{5}};

	VERIFY(v.count(0) == 1);
	VERIFY(v.count(1) == 2);
	VERIFY(v.count(2) == 0);
	VERIFY(v.count(3) == 0);
	VERIFY(v.count(4) == 1);
	VERIFY(v.count(5) == 3);
	VERIFY(v.count(6) == 0);

	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, CountHeterogeneousTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace count_heterogeneous_test

}	// namespace hamon_multiset_test

#endif
