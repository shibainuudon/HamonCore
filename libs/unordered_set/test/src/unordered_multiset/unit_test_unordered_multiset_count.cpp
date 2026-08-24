/**
 *	@file	unit_test_unordered_multiset_count.cpp
 *
 *	@brief	count のテスト
 *
 *	constexpr size_type count(const key_type& k) const;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

namespace hamon_unordered_multiset_test
{

namespace count_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().count(hamon::declval<Key const&>())), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().count(hamon::declval<Key const&>())), SizeType>::value, "");
	//static_assert( noexcept(hamon::declval<Set&>().count(hamon::declval<Key const&>())), "");
	//static_assert( noexcept(hamon::declval<Set const&>().count(hamon::declval<Key const&>())), "");

	Set const v{Key{3}, Key{1}, Key{4}, Key{1}};
	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 2);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 1);
	VERIFY(v.count(Key{4}) == 1);
	VERIFY(v.count(Key{5}) == 0);

	return true;
}

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test_noexcept()
{
	{
		using Set = hamon::unordered_multiset<Key, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Set&>().count(hamon::declval<Key const&>())), "");
		static_assert( noexcept(hamon::declval<Set const&>().count(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().count(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().count(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().count(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().count(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, ThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().count(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().count(hamon::declval<Key const&>())), "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, CountTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<float>()));
}

}	// namespace count_test

}	// namespace hamon_unordered_multiset_test
