/**
 *	@file	unit_test_unordered_multiset_contains_heterogeneous.cpp
 *
 *	@brief	contains のテスト
 *
 *	template<class K>
 *	constexpr bool contains(const K& k) const;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

// P0458R2
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) || (HAMON_CXX_STANDARD >= 20)

namespace hamon_unordered_multiset_test
{

namespace contains_heterogeneous_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::unordered_multiset<Key, decltype(hamon::ranges::hash), hamon::equal_to<>>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().contains(hamon::declval<int>())), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().contains(hamon::declval<int>())), bool>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().contains(hamon::declval<int>())), "");
	static_assert(!noexcept(hamon::declval<Set const&>().contains(hamon::declval<int>())), "");

	return true;
}

template <typename Set, typename K, typename = void>
struct is_contains_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_contains_invocable<Set, K, hamon::void_t<decltype(hamon::declval<Set>().contains(hamon::declval<K>()))>>
	: public hamon::true_type {};

struct S
{
	int value;

	friend constexpr bool operator==(S const& lhs, S const& rhs)
	{
		return lhs.value == rhs.value;
	}

	friend constexpr bool operator==(S const& lhs, int rhs)
	{
		return lhs.value == rhs;
	}

	friend constexpr bool operator==(int lhs, S const& rhs)
	{
		return lhs == rhs.value;
	}

	constexpr hamon::size_t hash() const { return hamon::hash<int>{}(value); }
};

UNORDERED_MULTISET_TEST_CONSTEXPR bool test2()
{
	using Set1 = hamon::unordered_multiset<S>;
	using Set2 = hamon::unordered_multiset<S, decltype(hamon::ranges::hash)>;
	using Set3 = hamon::unordered_multiset<S, hamon::hash<S>, hamon::equal_to<>>;
	using Set4 = hamon::unordered_multiset<S, decltype(hamon::ranges::hash), hamon::equal_to<>>;

	static_assert(!is_contains_invocable<Set1&, int>::value, "");
	static_assert(!is_contains_invocable<Set2&, int>::value, "");
	static_assert(!is_contains_invocable<Set3&, int>::value, "");
	static_assert( is_contains_invocable<Set4&, int>::value, "");

	static_assert(!is_contains_invocable<Set1 const&, int>::value, "");
	static_assert(!is_contains_invocable<Set2 const&, int>::value, "");
	static_assert(!is_contains_invocable<Set3 const&, int>::value, "");
	static_assert( is_contains_invocable<Set4 const&, int>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, ContainsHeterogeneousTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test2());
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace contains_heterogeneous_test

}	// namespace hamon_unordered_multiset_test

#endif
