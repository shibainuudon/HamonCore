/**
 *	@file	unit_test_unordered_set_find.cpp
 *
 *	@brief	find のテスト
 *
 *	constexpr iterator         find(const key_type& k);
 *	constexpr const_iterator   find(const key_type& k) const;
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

namespace hamon_unordered_set_test
{

namespace find_test
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
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().find(hamon::declval<Key const&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), ConstIterator>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_SET)
	//static_assert( noexcept(hamon::declval<Set&>().find(hamon::declval<Key const&>())), "");
	//static_assert( noexcept(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), "");
#endif

	{
		Set v{Key{3}, Key{1}, Key{4}, Key{1}};
		{
			auto it = v.find(Key{0});
			VERIFY(it == v.end());
		}
		{
			auto it = v.find(Key{1});
			VERIFY(it != v.end());
			VERIFY(*it == Key{1});
		}
		{
			auto it = v.find(Key{2});
			VERIFY(it == v.end());
		}
		{
			auto it = v.find(Key{3});
			VERIFY(it != v.end());
			VERIFY(*it == Key{3});
		}
	}
	{
		Set const v{Key{3}, Key{1}, Key{4}, Key{1}};
		{
			auto it = v.find(Key{0});
			VERIFY(it == v.end());
		}
		{
			auto it = v.find(Key{1});
			VERIFY(it != v.end());
			VERIFY(*it == Key{1});
		}
		{
			auto it = v.find(Key{2});
			VERIFY(it == v.end());
		}
		{
			auto it = v.find(Key{3});
			VERIFY(it != v.end());
			VERIFY(*it == Key{3});
		}
	}

	return true;
}

template <typename Key>
UNORDERED_SET_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_SET)
	{
		using Set = hamon::unordered_set<Key, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Set&>().find(hamon::declval<Key const&>())), "");
		static_assert( noexcept(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().find(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().find(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, ThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().find(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, FindTest)
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

}	// namespace find_test

}	// namespace hamon_unordered_set_test
