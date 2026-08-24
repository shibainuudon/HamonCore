/**
 *	@file	unit_test_unordered_multiset_find.cpp
 *
 *	@brief	find のテスト
 *
 *	constexpr iterator         find(const key_type& k);
 *	constexpr const_iterator   find(const key_type& k) const;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

namespace hamon_unordered_multiset_test
{

namespace find_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().find(hamon::declval<Key const&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), ConstIterator>::value, "");
	//static_assert( noexcept(hamon::declval<Set&>().find(hamon::declval<Key const&>())), "");
	//static_assert( noexcept(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), "");

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
HAMON_CXX20_CONSTEXPR bool test_noexcept()
{
	{
		using Set = hamon::unordered_multiset<Key, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Set&>().find(hamon::declval<Key const&>())), "");
		static_assert( noexcept(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().find(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().find(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_multiset<Key, ThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().find(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, FindTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<float>()));
}

}	// namespace find_test

}	// namespace hamon_unordered_multiset_test
