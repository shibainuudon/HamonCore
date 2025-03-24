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

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
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
	using Set = hamon::unordered_multiset<Key>;
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<Iterator>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>())), Iterator>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
	//static_assert( noexcept(hamon::declval<Set&>().erase(hamon::declval<Iterator>())), "");
	//static_assert( noexcept(hamon::declval<Set&>().erase(hamon::declval<ConstIterator>())), "");
#endif

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
UNORDERED_MULTISET_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
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
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, ErasePositionTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));

	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace erase_position_test

}	// namespace hamon_unordered_multiset_test
