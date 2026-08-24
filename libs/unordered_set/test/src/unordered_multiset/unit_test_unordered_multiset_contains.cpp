/**
 *	@file	unit_test_unordered_multiset_contains.cpp
 *
 *	@brief	contains のテスト
 *
 *	constexpr bool contains(const key_type& k) const;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

namespace hamon_unordered_multiset_test
{

namespace contains_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().contains(hamon::declval<Key const&>())), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().contains(hamon::declval<Key const&>())), bool>::value, "");
	//static_assert( noexcept(hamon::declval<Set&>().contains(hamon::declval<Key const&>())), "");
	//static_assert( noexcept(hamon::declval<Set const&>().contains(hamon::declval<Key const&>())), "");

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
HAMON_CXX20_CONSTEXPR bool test_noexcept()
{
	{
		using Set = hamon::unordered_multiset<Key, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Set&>().contains(hamon::declval<Key const&>())), "");
		static_assert( noexcept(hamon::declval<Set const&>().contains(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().contains(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().contains(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().contains(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().contains(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, ThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().contains(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().contains(hamon::declval<Key const&>())), "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, ContainsTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<float>()));
}

}	// namespace contains_test

}	// namespace hamon_unordered_multiset_test
