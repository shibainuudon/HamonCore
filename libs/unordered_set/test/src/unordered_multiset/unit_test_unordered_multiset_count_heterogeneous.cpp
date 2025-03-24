/**
 *	@file	unit_test_unordered_multiset_count_heterogeneous.cpp
 *
 *	@brief	count のテスト
 *
 *	template<class K>
 *	constexpr size_type count(const K& k) const;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) || \
	defined(__cpp_lib_generic_unordered_lookup) && (__cpp_lib_generic_unordered_lookup >= 201811L)

namespace hamon_unordered_multiset_test
{

namespace count_heterogeneous_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Set, typename K, typename = void>
struct is_count_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_count_invocable<Set, K, hamon::void_t<decltype(hamon::declval<Set>().count(hamon::declval<K>()))>>
	: public hamon::true_type {};

UNORDERED_MULTISET_TEST_CONSTEXPR bool test()
{
	using Key = TransparentKey;
	using Set1 = hamon::unordered_multiset<Key>;
	using Set2 = hamon::unordered_multiset<Key, hamon::remove_const_t<TransparentHash>>;
	using Set3 = hamon::unordered_multiset<Key, hamon::hash<Key>, hamon::equal_to<>>;
	using Set4 = hamon::unordered_multiset<Key, hamon::remove_const_t<TransparentHash>, hamon::equal_to<>>;

	static_assert(!is_count_invocable<Set1&, int>::value, "");
	static_assert(!is_count_invocable<Set2&, int>::value, "");
	static_assert(!is_count_invocable<Set3&, int>::value, "");
	static_assert( is_count_invocable<Set4&, int>::value, "");

	static_assert(!is_count_invocable<Set1 const&, int>::value, "");
	static_assert(!is_count_invocable<Set2 const&, int>::value, "");
	static_assert(!is_count_invocable<Set3 const&, int>::value, "");
	static_assert( is_count_invocable<Set4 const&, int>::value, "");

	using Set = Set4;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().count(hamon::declval<int>())), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().count(hamon::declval<int>())), SizeType>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
	//static_assert( noexcept(hamon::declval<Set&>().count(hamon::declval<int>())), "");
	//static_assert( noexcept(hamon::declval<Set const&>().count(hamon::declval<int>())), "");
#endif

	Set const v{Key{3}, Key{1}, Key{4}, Key{5}, Key{1}, Key{5}};
	VERIFY(v.count(0) == 0);
	VERIFY(v.count(1) == 2);
	VERIFY(v.count(2) == 0);
	VERIFY(v.count(3) == 1);
	VERIFY(v.count(4) == 1);
	VERIFY(v.count(5) == 2);

	return true;
}

UNORDERED_MULTISET_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
	using Key = TransparentKey;
	{
		using Set = hamon::unordered_multiset<Key, NoThrowHash<>, NoThrowEqualTo<>>;
		static_assert( noexcept(hamon::declval<Set&>().count(hamon::declval<int>())), "");
		static_assert( noexcept(hamon::declval<Set const&>().count(hamon::declval<int>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, NoThrowHash<>, ThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Set&>().count(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().count(hamon::declval<int>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, ThrowHash<>, NoThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Set&>().count(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().count(hamon::declval<int>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, ThrowHash<>, ThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Set&>().count(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().count(hamon::declval<int>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, CountHeterogeneousTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test());

	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test_noexcept());
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace count_heterogeneous_test

}	// namespace hamon_unordered_multiset_test

#endif
