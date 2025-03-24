/**
 *	@file	unit_test_unordered_multimap_equal_range_heterogeneous.cpp
 *
 *	@brief	equal_range のテスト
 *
 *	template<class K>
*	constexpr pair<iterator, iterator>             equal_range(const K& k);
*	template<class K>
*	constexpr pair<const_iterator, const_iterator> equal_range(const K& k) const;
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) || \
	defined(__cpp_lib_generic_unordered_lookup) && (__cpp_lib_generic_unordered_lookup >= 201811L)

namespace hamon_unordered_multimap_test
{

namespace equal_range_heterogeneous_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Map, typename K, typename = void>
struct is_equal_range_invocable
	: public hamon::false_type {};

template <typename Map, typename K>
struct is_equal_range_invocable<Map, K, hamon::void_t<decltype(hamon::declval<Map>().equal_range(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Key = TransparentKey;
	using Map1 = hamon::unordered_multimap<Key, T>;
	using Map2 = hamon::unordered_multimap<Key, T, TransparentHash>;
	using Map3 = hamon::unordered_multimap<Key, T, hamon::hash<Key>, hamon::equal_to<>>;
	using Map4 = hamon::unordered_multimap<Key, T, TransparentHash, hamon::equal_to<>>;

	static_assert(!is_equal_range_invocable<Map1&, int>::value, "");
	static_assert(!is_equal_range_invocable<Map2&, int>::value, "");
	static_assert(!is_equal_range_invocable<Map3&, int>::value, "");
	static_assert( is_equal_range_invocable<Map4&, int>::value, "");

	static_assert(!is_equal_range_invocable<Map1 const&, int>::value, "");
	static_assert(!is_equal_range_invocable<Map2 const&, int>::value, "");
	static_assert(!is_equal_range_invocable<Map3 const&, int>::value, "");
	static_assert( is_equal_range_invocable<Map4 const&, int>::value, "");

	using Map = Map4;
	using SizeType = typename Map::size_type;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;
#if defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	using Result1 = std::pair<Iterator, Iterator>;
	using Result2 = std::pair<ConstIterator, ConstIterator>;
#else
	using Result1 = hamon::pair<Iterator, Iterator>;
	using Result2 = hamon::pair<ConstIterator, ConstIterator>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().equal_range(hamon::declval<int>())), Result1>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().equal_range(hamon::declval<int>())), Result2>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	//static_assert( noexcept(hamon::declval<Map&>().equal_range(hamon::declval<int>())), "");
	//static_assert( noexcept(hamon::declval<Map const&>().equal_range(hamon::declval<int>())), "");
#endif

	{
		auto check = [](Map& v, int k, SizeType size)
		{
			auto r = v.equal_range(k);
			VERIFY(SizeType(hamon::distance(r.first, r.second)) == size);
			for (auto it = r.first; it != r.second; ++it)
			{
				VERIFY(it->first == k);
			}
			return true;
		};

		Map v
		{
			{Key{5}, T{60}},
			{Key{7}, T{70}},
			{Key{3}, T{40}},
			{Key{3}, T{30}},
			{Key{2}, T{10}},
			{Key{3}, T{50}},
			{Key{2}, T{20}},
		};

		VERIFY(check(v, 0, 0));
		VERIFY(check(v, 1, 0));
		VERIFY(check(v, 2, 2));
		VERIFY(check(v, 3, 3));
		VERIFY(check(v, 4, 0));
		VERIFY(check(v, 5, 1));
		VERIFY(check(v, 6, 0));
		VERIFY(check(v, 7, 1));
	}
	{
		auto check = [](Map const& v, int k, SizeType size)
		{
			auto r = v.equal_range(k);
			VERIFY(SizeType(hamon::distance(r.first, r.second)) == size);
			for (auto it = r.first; it != r.second; ++it)
			{
				VERIFY(it->first == k);
			}
			return true;
		};

		Map const v
		{
			{Key{5}, T{60}},
			{Key{7}, T{70}},
			{Key{3}, T{40}},
			{Key{3}, T{30}},
			{Key{2}, T{10}},
			{Key{3}, T{50}},
			{Key{2}, T{20}},
		};

		VERIFY(check(v, 0, 0));
		VERIFY(check(v, 1, 0));
		VERIFY(check(v, 2, 2));
		VERIFY(check(v, 3, 3));
		VERIFY(check(v, 4, 0));
		VERIFY(check(v, 5, 1));
		VERIFY(check(v, 6, 0));
		VERIFY(check(v, 7, 1));
	}

	return true;
}

template <typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	using Key = TransparentKey;
	{
		using Map = hamon::unordered_multimap<Key, T, NoThrowHash<>, NoThrowEqualTo<>>;
		static_assert( noexcept(hamon::declval<Map&>().equal_range(hamon::declval<int>())), "");
		static_assert( noexcept(hamon::declval<Map const&>().equal_range(hamon::declval<int>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, NoThrowHash<>, ThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Map&>().equal_range(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().equal_range(hamon::declval<int>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, ThrowHash<>, NoThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Map&>().equal_range(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().equal_range(hamon::declval<int>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, ThrowHash<>, ThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Map&>().equal_range(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().equal_range(hamon::declval<int>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, EqualRangeHeterogeneousTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());

	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test_noexcept<int>());
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test_noexcept<char>());
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test_noexcept<float>());
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace equal_range_heterogeneous_test

}	// namespace hamon_unordered_multimap_test

#endif
