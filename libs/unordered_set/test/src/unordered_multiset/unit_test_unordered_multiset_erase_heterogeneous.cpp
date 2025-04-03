/**
 *	@file	unit_test_unordered_multiset_erase_heterogeneous.cpp
 *
 *	@brief	erase のテスト
 *
 *	template<class K> constexpr size_type erase(K&& x);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) || \
	(defined(__cpp_lib_associative_heterogeneous_erasure) && (__cpp_lib_associative_heterogeneous_erasure >= 202110L))

namespace hamon_unordered_multiset_test
{

namespace erase_heterogeneous_test
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
UNORDERED_MULTISET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key, decltype(hamon::ranges::hash), hamon::equal_to<>>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<int>())), SizeType>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
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

UNORDERED_MULTISET_TEST_CONSTEXPR bool test2()
{
	using Set1 = hamon::unordered_multiset<TransparentKey>;
	using Set2 = hamon::unordered_multiset<TransparentKey, decltype(hamon::ranges::hash)>;
	using Set3 = hamon::unordered_multiset<TransparentKey, hamon::hash<TransparentKey>, hamon::equal_to<>>;
	using Set4 = hamon::unordered_multiset<TransparentKey, decltype(hamon::ranges::hash), hamon::equal_to<>>;

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

GTEST_TEST(UnorderedMultisetTest, EraseHeterogeneousTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));

	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace erase_heterogeneous_test

}	// namespace hamon_unordered_multiset_test

#endif
