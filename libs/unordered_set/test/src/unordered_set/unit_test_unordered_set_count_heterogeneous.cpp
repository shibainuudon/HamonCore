/**
 *	@file	unit_test_unordered_set_count_heterogeneous.cpp
 *
 *	@brief	count のテスト
 *
 *	template<class K>
 *	constexpr size_type count(const K& k) const;
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_SET) || \
	defined(__cpp_lib_generic_unordered_lookup) && (__cpp_lib_generic_unordered_lookup >= 201811L)

namespace hamon_unordered_set_test
{

namespace count_heterogeneous_test
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

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().count(hamon::declval<int>())), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().count(hamon::declval<int>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().count(hamon::declval<int>())), "");
	static_assert(!noexcept(hamon::declval<Set const&>().count(hamon::declval<int>())), "");

	return true;
}

template <typename Set, typename K, typename = void>
struct is_count_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_count_invocable<Set, K, hamon::void_t<decltype(hamon::declval<Set>().count(hamon::declval<K>()))>>
	: public hamon::true_type {};

UNORDERED_SET_TEST_CONSTEXPR bool test2()
{
	using Set1 = hamon::unordered_set<TransparentKey>;
	using Set2 = hamon::unordered_set<TransparentKey, decltype(hamon::ranges::hash)>;
	using Set3 = hamon::unordered_set<TransparentKey, hamon::hash<TransparentKey>, hamon::equal_to<>>;
	using Set4 = hamon::unordered_set<TransparentKey, decltype(hamon::ranges::hash), hamon::equal_to<>>;

	static_assert(!is_count_invocable<Set1&, int>::value, "");
	static_assert(!is_count_invocable<Set2&, int>::value, "");
	static_assert(!is_count_invocable<Set3&, int>::value, "");
	static_assert( is_count_invocable<Set4&, int>::value, "");

	static_assert(!is_count_invocable<Set1 const&, int>::value, "");
	static_assert(!is_count_invocable<Set2 const&, int>::value, "");
	static_assert(!is_count_invocable<Set3 const&, int>::value, "");
	static_assert( is_count_invocable<Set4 const&, int>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, CountHeterogeneousTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE(test2());
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace count_heterogeneous_test

}	// namespace hamon_unordered_set_test

#endif
