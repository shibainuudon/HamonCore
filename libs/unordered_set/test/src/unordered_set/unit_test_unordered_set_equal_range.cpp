/**
 *	@file	unit_test_unordered_set_equal_range.cpp
 *
 *	@brief	equal_range のテスト
 *
 *	constexpr pair<iterator, iterator>               equal_range(const key_type& k);
 *	constexpr pair<const_iterator, const_iterator>   equal_range(const key_type& k) const;
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

namespace hamon_unordered_set_test
{

namespace equal_range_test
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
	using SizeType = typename Set::size_type;
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;
#if defined(HAMON_USE_STD_UNORDERED_SET)
	using Result1 = std::pair<Iterator, Iterator>;
	using Result2 = std::pair<ConstIterator, ConstIterator>;
#else
	using Result1 = hamon::pair<Iterator, Iterator>;
	using Result2 = hamon::pair<ConstIterator, ConstIterator>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().equal_range(hamon::declval<Key const&>())), Result1>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().equal_range(hamon::declval<Key const&>())), Result2>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_SET)
	//static_assert( noexcept(hamon::declval<Set&>().equal_range(hamon::declval<Key const&>())), "");
	//static_assert( noexcept(hamon::declval<Set const&>().equal_range(hamon::declval<Key const&>())), "");
#endif

	{
		auto check = [](Set& v, Key k, SizeType size)
		{
			auto r = v.equal_range(k);
			VERIFY(SizeType(hamon::distance(r.first, r.second)) == size);
			for (auto it = r.first; it != r.second; ++it)
			{
				VERIFY(*it == k);
			}
			if (size == 0)
			{
				VERIFY(r.first == v.end());
				VERIFY(r.second == v.end());
			}
			return true;
		};

		Set v{Key{3}, Key{1}, Key{4}, Key{1}, Key{4}};

		VERIFY(check(v, Key{0}, 0));
		VERIFY(check(v, Key{1}, 1));
		VERIFY(check(v, Key{2}, 0));
		VERIFY(check(v, Key{3}, 1));
		VERIFY(check(v, Key{4}, 1));
		VERIFY(check(v, Key{5}, 0));
	}
	{
		auto check = [](Set const& v, Key k, SizeType size)
		{
			auto r = v.equal_range(k);
			VERIFY(SizeType(hamon::distance(r.first, r.second)) == size);
			for (auto it = r.first; it != r.second; ++it)
			{
				VERIFY(*it == k);
			}
			if (size == 0)
			{
				VERIFY(r.first == v.end());
				VERIFY(r.second == v.end());
			}
			return true;
		};

		Set const v{Key{3}, Key{1}, Key{4}, Key{1}, Key{5}};

		VERIFY(check(v, Key{0}, 0));
		VERIFY(check(v, Key{1}, 1));
		VERIFY(check(v, Key{2}, 0));
		VERIFY(check(v, Key{3}, 1));
		VERIFY(check(v, Key{4}, 1));
		VERIFY(check(v, Key{5}, 1));
	}

	return true;
}

template <typename Key>
UNORDERED_SET_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_SET)
	{
		using Set = hamon::unordered_set<Key, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Set&>().equal_range(hamon::declval<Key const&>())), "");
		static_assert( noexcept(hamon::declval<Set const&>().equal_range(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().equal_range(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().equal_range(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().equal_range(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().equal_range(hamon::declval<Key const&>())), "");
	}
	{
		using Set = hamon::unordered_set<Key, ThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Set&>().equal_range(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Set const&>().equal_range(hamon::declval<Key const&>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, EqualRangeTest)
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

}	// namespace equal_range_test

}	// namespace hamon_unordered_set_test
