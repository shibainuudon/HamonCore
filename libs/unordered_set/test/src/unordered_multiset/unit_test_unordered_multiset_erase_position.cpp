/**
 *	@file	unit_test_unordered_multiset_erase_position.cpp
 *
 *	@brief	erase のテスト
 *
 *	constexpr iterator  erase(iterator position)
 *		requires (!same_as<iterator, const_iterator>);
 *	constexpr iterator  erase(const_iterator position);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

namespace hamon_unordered_multiset_test
{

namespace erase_position_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<Iterator>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>())), Iterator>::value, "");
	//static_assert( noexcept(hamon::declval<Set&>().erase(hamon::declval<Iterator>())), "");
	//static_assert( noexcept(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>())), "");

	Set v{Key{2}, Key{2}, Key{7}, Key{8}, Key{6},};
	VERIFY(v.size() == 5);
	{
		auto i = v.begin();
		auto j = hamon::next(i);
		auto r = v.erase(i);
		VERIFY(r == j);
	}
	VERIFY(v.size() == 4);
	{
		auto i = hamon::next(v.cbegin(), 3);
		auto j = hamon::next(i);
		auto r = v.erase(i);
		VERIFY(r == j);
	}
	VERIFY(v.size() == 3);

	return true;
}

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test_noexcept()
{
	{
		using Set = hamon::unordered_multiset<Key, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		using Iterator = typename Set::iterator;
		using ConstIterator = typename Set::const_iterator;
		static_assert( noexcept(hamon::declval<Set&>().erase(hamon::declval<Iterator>())), "");
		static_assert( noexcept(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		using Iterator = typename Set::iterator;
		using ConstIterator = typename Set::const_iterator;
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<Iterator>())), "");
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		using Iterator = typename Set::iterator;
		using ConstIterator = typename Set::const_iterator;
		static_assert( noexcept(hamon::declval<Set&>().erase(hamon::declval<Iterator>())), "");
		static_assert( noexcept(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, ThrowHash<Key>, ThrowEqualTo<Key>>;
		using Iterator = typename Set::iterator;
		using ConstIterator = typename Set::const_iterator;
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<Iterator>())), "");
		static_assert(!noexcept(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>())), "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, ErasePositionTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<float>()));
}

}	// namespace erase_position_test

}	// namespace hamon_unordered_multiset_test
