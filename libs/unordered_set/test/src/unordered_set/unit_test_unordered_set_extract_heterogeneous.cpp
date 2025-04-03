/**
 *	@file	unit_test_unordered_set_extract_heterogeneous.cpp
 *
 *	@brief	extract のテスト
 *
 *	template<class K> constexpr node_type extract(K&& x);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_SET) || \
	(defined(__cpp_lib_associative_heterogeneous_erasure) && (__cpp_lib_associative_heterogeneous_erasure >= 202110L))

namespace hamon_unordered_set_test
{

namespace extract_heterogeneous_test
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
UNORDERED_SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::unordered_set<Key, decltype(hamon::ranges::hash), hamon::equal_to<>>;
	using NodeType = typename Set::node_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().extract(hamon::declval<int>())), NodeType>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().extract(hamon::declval<int>())), "");

	return true;
}

template <typename Set, typename K, typename = void>
struct is_extract_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_extract_invocable<Set, K, hamon::void_t<decltype(hamon::declval<Set>().extract(hamon::declval<K>()))>>
	: public hamon::true_type {};

UNORDERED_SET_TEST_CONSTEXPR bool test2()
{
	using Set1 = hamon::unordered_set<TransparentKey>;
	using Set2 = hamon::unordered_set<TransparentKey, decltype(hamon::ranges::hash)>;
	using Set3 = hamon::unordered_set<TransparentKey, hamon::hash<TransparentKey>, hamon::equal_to<>>;
	using Set4 = hamon::unordered_set<TransparentKey, decltype(hamon::ranges::hash), hamon::equal_to<>>;

	static_assert(!is_extract_invocable<Set1&, int>::value, "");
	static_assert(!is_extract_invocable<Set2&, int>::value, "");
	static_assert(!is_extract_invocable<Set3&, int>::value, "");
	static_assert( is_extract_invocable<Set4&, int>::value, "");

	static_assert(!is_extract_invocable<Set1 const&, int>::value, "");
	static_assert(!is_extract_invocable<Set2 const&, int>::value, "");
	static_assert(!is_extract_invocable<Set3 const&, int>::value, "");
	static_assert(!is_extract_invocable<Set4 const&, int>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, ExtractHeterogeneousTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));

	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE(test2());
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace extract_heterogeneous_test

}	// namespace hamon_unordered_set_test

#endif
