/**
 *	@file	unit_test_unordered_set_erase_heterogeneous.cpp
 *
 *	@brief	erase のテスト
 *
 *	template<class K> constexpr size_type erase(K&& x);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_SET) || \
	(defined(__cpp_lib_associative_heterogeneous_erasure) && (__cpp_lib_associative_heterogeneous_erasure >= 202110L))

namespace hamon_unordered_set_test
{

namespace erase_heterogeneous_test
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
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<int>())), SizeType>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_SET)
	static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<int>())), "");
#endif

	return true;
}

template <typename Set, typename K, typename = void>
struct is_erase_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_erase_invocable<Set, K, hamon::void_t<decltype(hamon::declval<Set>().erase(hamon::declval<K>()))>>
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

	static_assert(!is_erase_invocable<Set1&, int>::value, "");
	static_assert(!is_erase_invocable<Set2&, int>::value, "");
	static_assert(!is_erase_invocable<Set3&, int>::value, "");
	static_assert( is_erase_invocable<Set4&, int>::value, "");

	static_assert(!is_erase_invocable<Set1 const&, int>::value, "");
	static_assert(!is_erase_invocable<Set2 const&, int>::value, "");
	static_assert(!is_erase_invocable<Set3 const&, int>::value, "");
	static_assert(!is_erase_invocable<Set4 const&, int>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, EraseHeterogeneousTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test2()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace erase_heterogeneous_test

}	// namespace hamon_unordered_set_test

#endif
