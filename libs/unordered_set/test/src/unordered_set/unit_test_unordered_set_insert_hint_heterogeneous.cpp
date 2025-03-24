﻿/**
 *	@file	unit_test_unordered_set_insert_hint_heterogeneous.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class K> constexpr iterator insert(const_iterator hint, K&& obj);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_SET) || \
	(defined(__cpp_lib_associative_heterogeneous_insertion) && (__cpp_lib_associative_heterogeneous_insertion >= 202306L))

namespace hamon_unordered_set_test
{

namespace insert_hint_heterogeneous_test
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
UNORDERED_SET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::unordered_set<Key, decltype(hamon::ranges::hash), hamon::equal_to<>>;
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::declval<ConstIterator>(), hamon::declval<char>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().insert(hamon::declval<ConstIterator>(), hamon::declval<char>())), "");

	return true;
}

template <typename Set, typename K, typename = void>
struct is_insert_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_insert_invocable<Set, K, hamon::void_t<
	decltype(hamon::declval<Set>().insert(hamon::declval<typename Set::const_iterator>(), hamon::declval<K>()))>>
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

UNORDERED_SET_TEST_CONSTEXPR bool test2()
{
	using Set1 = hamon::unordered_set<S>;
	using Set2 = hamon::unordered_set<S, decltype(hamon::ranges::hash)>;
	using Set3 = hamon::unordered_set<S, hamon::hash<S>, hamon::equal_to<>>;
	using Set4 = hamon::unordered_set<S, decltype(hamon::ranges::hash), hamon::equal_to<>>;

	static_assert(!is_insert_invocable<Set1&, int>::value, "");
	static_assert(!is_insert_invocable<Set2&, int>::value, "");
	static_assert(!is_insert_invocable<Set3&, int>::value, "");
	static_assert( is_insert_invocable<Set4&, int>::value, "");

	static_assert(!is_insert_invocable<Set1 const&, int>::value, "");
	static_assert(!is_insert_invocable<Set2 const&, int>::value, "");
	static_assert(!is_insert_invocable<Set3 const&, int>::value, "");
	static_assert(!is_insert_invocable<Set4 const&, int>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, InsertHintHeterogeneousTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE(test2());
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace insert_hint_heterogeneous_test

}	// namespace hamon_unordered_set_test

#endif
