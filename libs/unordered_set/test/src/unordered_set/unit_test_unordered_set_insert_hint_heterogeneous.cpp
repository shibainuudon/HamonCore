/**
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
#include "unordered_set_test_helper.hpp"

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

template <typename Set, typename I, typename K, typename = void>
struct is_insert_invocable
	: public hamon::false_type {};

template <typename Set, typename I, typename K>
struct is_insert_invocable<Set, I, K, hamon::void_t<
	decltype(hamon::declval<Set>().insert(hamon::declval<I>(), hamon::declval<K>()))>>
	: public hamon::true_type {};

UNORDERED_SET_TEST_CONSTEXPR bool test2()
{
	using Set1 = hamon::unordered_set<TransparentKey>;
	using Set2 = hamon::unordered_set<TransparentKey, decltype(hamon::ranges::hash)>;
	using Set3 = hamon::unordered_set<TransparentKey, hamon::hash<TransparentKey>, hamon::equal_to<>>;
	using Set4 = hamon::unordered_set<TransparentKey, decltype(hamon::ranges::hash), hamon::equal_to<>>;

	static_assert(!is_insert_invocable<Set1&, typename Set1::const_iterator, int>::value, "");
	static_assert(!is_insert_invocable<Set2&, typename Set2::const_iterator, int>::value, "");
	static_assert(!is_insert_invocable<Set3&, typename Set3::const_iterator, int>::value, "");
	static_assert( is_insert_invocable<Set4&, typename Set4::const_iterator, int>::value, "");

	static_assert(!is_insert_invocable<Set1 const&, typename Set1::const_iterator, int>::value, "");
	static_assert(!is_insert_invocable<Set2 const&, typename Set2::const_iterator, int>::value, "");
	static_assert(!is_insert_invocable<Set3 const&, typename Set3::const_iterator, int>::value, "");
	static_assert(!is_insert_invocable<Set4 const&, typename Set4::const_iterator, int>::value, "");

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
