/**
 *	@file	unit_test_unordered_set_erase_iterator.cpp
 *
 *	@brief	erase のテスト
 *
 *	constexpr iterator  erase(const_iterator first, const_iterator last);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

namespace hamon_unordered_set_test
{

namespace erase_iterator_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_set<Key>;
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>(), hamon::declval<ConstIterator>())), Iterator>::value, "");
	//static_assert( noexcept(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>(), hamon::declval<ConstIterator>())), "");

	{
		Set v{Key{2}, Key{4}, Key{7}, Key{8}, Key{6},};
		VERIFY(v.size() == 5);
		{
			auto i = v.begin();
			auto j = v.end();
			auto r = v.erase(i, j);
			VERIFY(r == j);
		}
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test_noexcept()
{
	{
		using Set = hamon::unordered_set<Key, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		using ConstIterator = typename Set::const_iterator;
		static_assert( noexcept(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>(), hamon::declval<ConstIterator>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		using ConstIterator = typename Set::const_iterator;
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>(), hamon::declval<ConstIterator>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		using ConstIterator = typename Set::const_iterator;
		static_assert( noexcept(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>(), hamon::declval<ConstIterator>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, ThrowHash<Key>, ThrowEqualTo<Key>>;
		using ConstIterator = typename Set::const_iterator;
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>(), hamon::declval<ConstIterator>())), "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, EraseIteratorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<float>()));
}

}	// namespace erase_iterator_test

}	// namespace hamon_unordered_set_test
