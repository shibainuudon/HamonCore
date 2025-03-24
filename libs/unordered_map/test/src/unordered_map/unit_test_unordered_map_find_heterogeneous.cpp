/**
 *	@file	unit_test_unordered_map_find_heterogeneous.cpp
 *
 *	@brief	find のテスト
 *
 *	template<class K>
 *	constexpr iterator       find(const K& k);
 *	template<class K>
 *	constexpr const_iterator find(const K& k) const;
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MAP) || \
	defined(__cpp_lib_generic_unordered_lookup) && (__cpp_lib_generic_unordered_lookup >= 201811L)

namespace hamon_unordered_map_test
{

namespace find_heterogeneous_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Map, typename K, typename = void>
struct is_find_invocable
	: public hamon::false_type {};

template <typename Map, typename K>
struct is_find_invocable<Map, K, hamon::void_t<decltype(hamon::declval<Map>().find(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test()
{
	using Key = TransparentKey;
	using Map1 = hamon::unordered_map<Key, T>;
	using Map2 = hamon::unordered_map<Key, T, TransparentHash>;
	using Map3 = hamon::unordered_map<Key, T, hamon::hash<Key>, hamon::equal_to<>>;
	using Map4 = hamon::unordered_map<Key, T, TransparentHash, hamon::equal_to<>>;

	static_assert(!is_find_invocable<Map1&, int>::value, "");
	static_assert(!is_find_invocable<Map2&, int>::value, "");
	static_assert(!is_find_invocable<Map3&, int>::value, "");
	static_assert( is_find_invocable<Map4&, int>::value, "");

	static_assert(!is_find_invocable<Map1 const&, int>::value, "");
	static_assert(!is_find_invocable<Map2 const&, int>::value, "");
	static_assert(!is_find_invocable<Map3 const&, int>::value, "");
	static_assert( is_find_invocable<Map4 const&, int>::value, "");

	using Map = Map4;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().find(hamon::declval<int>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().find(hamon::declval<int>())), ConstIterator>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
	//static_assert( noexcept(hamon::declval<Map&>().find(hamon::declval<int>())), "");
	//static_assert( noexcept(hamon::declval<Map const&>().find(hamon::declval<int>())), "");
#endif

	{
		Map v
		{
			{Key{0}, T{10}},
			{Key{2}, T{20}},
			{Key{4}, T{30}},
			{Key{0}, T{40}},
			{Key{4}, T{50}},
			{Key{0}, T{60}},
			{Key{1}, T{70}},
		};

		VERIFY(v.find(0) != v.end());
		VERIFY(v.find(1) != v.end());
		VERIFY(v.find(2) != v.end());
		VERIFY(v.find(3) == v.end());
		VERIFY(v.find(4) != v.end());
		VERIFY(v.find(5) == v.end());

		VERIFY(v.find(0)->first == Key{0});
		VERIFY(v.find(1)->first == Key{1});
		VERIFY(v.find(1)->second == T{70});
		VERIFY(v.find(2)->first == Key{2});
		VERIFY(v.find(2)->second == T{20});
		VERIFY(v.find(4)->first == Key{4});
	}
	{
		Map const v
		{
			{Key{0}, T{10}},
			{Key{2}, T{20}},
			{Key{4}, T{30}},
			{Key{0}, T{40}},
			{Key{4}, T{50}},
			{Key{0}, T{60}},
			{Key{1}, T{70}},
		};

		VERIFY(v.find(0) != v.end());
		VERIFY(v.find(1) != v.end());
		VERIFY(v.find(2) != v.end());
		VERIFY(v.find(3) == v.end());
		VERIFY(v.find(4) != v.end());
		VERIFY(v.find(5) == v.end());

		VERIFY(v.find(0)->first == Key{0});
		VERIFY(v.find(1)->first == Key{1});
		VERIFY(v.find(1)->second == T{70});
		VERIFY(v.find(2)->first == Key{2});
		VERIFY(v.find(2)->second == T{20});
		VERIFY(v.find(4)->first == Key{4});
	}

	return true;
}

template <typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
	using Key = TransparentKey;
	{
		using Map = hamon::unordered_map<Key, T, NoThrowHash<>, NoThrowEqualTo<>>;
		static_assert( noexcept(hamon::declval<Map&>().find(hamon::declval<int>())), "");
		static_assert( noexcept(hamon::declval<Map const&>().find(hamon::declval<int>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, NoThrowHash<>, ThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Map&>().find(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().find(hamon::declval<int>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, ThrowHash<>, NoThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Map&>().find(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().find(hamon::declval<int>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, ThrowHash<>, ThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Map&>().find(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().find(hamon::declval<int>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, FindHeterogeneousTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());

	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test_noexcept<int>());
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test_noexcept<char>());
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test_noexcept<float>());
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace find_heterogeneous_test

}	// namespace hamon_unordered_map_test

#endif
