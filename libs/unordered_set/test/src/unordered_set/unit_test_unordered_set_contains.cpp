/**
 *	@file	unit_test_unordered_set_contains.cpp
 *
 *	@brief	contains のテスト
 *
 *	constexpr bool contains(const key_type& k) const;
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

// P0458R2
#if !defined(HAMON_USE_STD_UNORDERED_SET) || (HAMON_CXX_STANDARD >= 20)

namespace hamon_unordered_set_test
{

namespace contains_test
{

#if !defined(HAMON_USE_STD_UNORDERED_SET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
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
	using Set = hamon::unordered_set<Key>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().contains(hamon::declval<Key const&>())), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().contains(hamon::declval<Key const&>())), bool>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_SET)
	//static_assert( noexcept(hamon::declval<Set&>().contains(hamon::declval<Key const&>())), "");
	//static_assert( noexcept(hamon::declval<Set const&>().contains(hamon::declval<Key const&>())), "");
#endif

	Set const v{Key{3}, Key{1}, Key{4}, Key{1}};
	VERIFY(!v.contains(Key{0}));
	VERIFY( v.contains(Key{1}));
	VERIFY(!v.contains(Key{2}));
	VERIFY( v.contains(Key{3}));
	VERIFY( v.contains(Key{4}));
	VERIFY(!v.contains(Key{5}));

	return true;
}

template <typename Key>
UNORDERED_SET_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_SET)
	{
		using Set = hamon::unordered_set<Key, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Set&>().contains(hamon::declval<Key const&>())), "");
		static_assert( noexcept(hamon::declval<Set const&>().contains(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().contains(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().contains(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().contains(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().contains(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, ThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().contains(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().contains(hamon::declval<Key const&>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, ContainsTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));

	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace contains_test

}	// namespace hamon_unordered_set_test

#endif
