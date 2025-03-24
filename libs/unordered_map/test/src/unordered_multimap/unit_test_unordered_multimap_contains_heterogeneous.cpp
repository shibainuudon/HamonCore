/**
 *	@file	unit_test_unordered_multimap_contains_heterogeneous.cpp
 *
 *	@brief	contains のテスト
 *
 *	template<class K>
 *	constexpr bool contains(const K& k) const;
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
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

namespace contains_heterogeneous_test
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
struct is_contains_invocable
	: public hamon::false_type {};

template <typename Map, typename K>
struct is_contains_invocable<Map, K, hamon::void_t<decltype(hamon::declval<Map>().contains(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Key = TransparentKey;
	using Map1 = hamon::unordered_multimap<Key, T>;
	using Map2 = hamon::unordered_multimap<Key, T, TransparentHash>;
	using Map3 = hamon::unordered_multimap<Key, T, hamon::hash<Key>, hamon::equal_to<>>;
	using Map4 = hamon::unordered_multimap<Key, T, TransparentHash, hamon::equal_to<>>;

	static_assert(!is_contains_invocable<Map1&, int>::value, "");
	static_assert(!is_contains_invocable<Map2&, int>::value, "");
	static_assert(!is_contains_invocable<Map3&, int>::value, "");
	static_assert( is_contains_invocable<Map4&, int>::value, "");

	static_assert(!is_contains_invocable<Map1 const&, int>::value, "");
	static_assert(!is_contains_invocable<Map2 const&, int>::value, "");
	static_assert(!is_contains_invocable<Map3 const&, int>::value, "");
	static_assert( is_contains_invocable<Map4 const&, int>::value, "");

	using Map = Map4;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().contains(hamon::declval<int>())), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().contains(hamon::declval<int>())), bool>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	//static_assert( noexcept(hamon::declval<Map&>().contains(hamon::declval<int>())), "");
	//static_assert( noexcept(hamon::declval<Map const&>().contains(hamon::declval<int>())), "");
#endif

	Map const v
	{
		{Key{8}, T{10}},
		{Key{2}, T{20}},
		{Key{5}, T{30}},
		{Key{8}, T{40}},
		{Key{5}, T{50}},
		{Key{6}, T{60}},
		{Key{8}, T{70}},
	};

	VERIFY(v.contains(0) == false);
	VERIFY(v.contains(1) == false);
	VERIFY(v.contains(2) == true);
	VERIFY(v.contains(3) == false);
	VERIFY(v.contains(4) == false);
	VERIFY(v.contains(5) == true);
	VERIFY(v.contains(6) == true);
	VERIFY(v.contains(7) == false);
	VERIFY(v.contains(8) == true);
	VERIFY(v.contains(9) == false);

	return true;
}

template <typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	using Key = TransparentKey;
	{
		using Map = hamon::unordered_multimap<Key, T, NoThrowHash<>, NoThrowEqualTo<>>;
		static_assert( noexcept(hamon::declval<Map&>().contains(hamon::declval<int>())), "");
		static_assert( noexcept(hamon::declval<Map const&>().contains(hamon::declval<int>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, NoThrowHash<>, ThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Map&>().contains(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().contains(hamon::declval<int>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, ThrowHash<>, NoThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Map&>().contains(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().contains(hamon::declval<int>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, ThrowHash<>, ThrowEqualTo<>>;
		static_assert(!noexcept(hamon::declval<Map&>().contains(hamon::declval<int>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().contains(hamon::declval<int>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, ContainsHeterogeneousTest)
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

}	// namespace contains_heterogeneous_test

}	// namespace hamon_unordered_multimap_test

#endif
