/**
 *	@file	unit_test_unordered_map_erase_heterogeneous.cpp
 *
 *	@brief	erase のテスト
 *
 *	template<class K> constexpr size_type erase(K&& x);
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
	(defined(__cpp_lib_associative_heterogeneous_erasure) && (__cpp_lib_associative_heterogeneous_erasure >= 202110L))

namespace hamon_unordered_map_test
{

namespace erase_heterogeneous_test
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
struct is_erase_invocable
	: public hamon::false_type {};

template <typename Map, typename K>
struct is_erase_invocable<Map, K, hamon::void_t<decltype(hamon::declval<Map>().erase(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test()
{
	using Key = TransparentKey;
	using Map1 = hamon::unordered_map<Key, T>;
	using Map2 = hamon::unordered_map<Key, T, TransparentHash>;
	using Map3 = hamon::unordered_map<Key, T, hamon::hash<Key>, hamon::equal_to<>>;
	using Map4 = hamon::unordered_map<Key, T, TransparentHash, hamon::equal_to<>>;

	static_assert(!is_erase_invocable<Map1&, int>::value, "");
	static_assert(!is_erase_invocable<Map2&, int>::value, "");
	static_assert(!is_erase_invocable<Map3&, int>::value, "");
	static_assert( is_erase_invocable<Map4&, int>::value, "");

	static_assert(!is_erase_invocable<Map1 const&, int>::value, "");
	static_assert(!is_erase_invocable<Map2 const&, int>::value, "");
	static_assert(!is_erase_invocable<Map3 const&, int>::value, "");
	static_assert(!is_erase_invocable<Map4 const&, int>::value, "");

	using Map = Map4;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<int>())), SizeType>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
	//static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<int>())), "");
#endif

	Map v
	{
		{Key{10}, T{0}},
		{Key{20}, T{0}},
		{Key{40}, T{0}},
		{Key{80}, T{0}},
	};
	VERIFY(v.size() == 4);

	VERIFY(v.erase(0) == 0);
	VERIFY(v.size() == 4);

	VERIFY(v.erase(10) == 1);
	VERIFY(v.size() == 3);

	VERIFY(v.erase(20) == 1);
	VERIFY(v.size() == 2);

	VERIFY(v.erase(30) == 0);
	VERIFY(v.size() == 2);

	VERIFY(v.erase(40) == 1);
	VERIFY(v.size() == 1);

	VERIFY(v.erase(40) == 0);
	VERIFY(v.size() == 1);

	VERIFY(v.erase(80) == 1);
	VERIFY(v.size() == 0);

	return true;
}

template <typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
	using Key = TransparentKey;
	{
		using Map = hamon::unordered_map<Key, T, NoThrowHash<>, NoThrowEqualTo<>>;
		static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<int>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, NoThrowHash<>, ThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<int>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, ThrowHash<>, NoThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<int>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, ThrowHash<>, ThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<int>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, EraseHeterogeneousTest)
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

}	// namespace erase_heterogeneous_test

}	// namespace hamon_unordered_map_test

#endif
