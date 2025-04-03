/**
 *	@file	unit_test_unordered_map_try_emplace_hint_heterogeneous.cpp
 *
 *	@brief	try_emplace のテスト
 *
 *	template<class K, class... Args>
 *	constexpr iterator try_emplace(const_iterator hint, K&& k, Args&&... args);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MAP) || \
	(defined(__cpp_lib_associative_heterogeneous_insertion) && (__cpp_lib_associative_heterogeneous_insertion >= 202306L))

namespace hamon_unordered_map_test
{

namespace try_emplace_hint_heterogeneous_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MAP)
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::unordered_map<Key, T, decltype(hamon::ranges::hash), hamon::equal_to<>>;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().try_emplace(hamon::declval<ConstIterator>(), hamon::declval<int const&>(), hamon::declval<T>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().try_emplace(hamon::declval<ConstIterator>(), hamon::declval<int&&>(), hamon::declval<T>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().try_emplace(hamon::declval<ConstIterator>(), hamon::declval<int const&>(), hamon::declval<T>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().try_emplace(hamon::declval<ConstIterator>(), hamon::declval<int&&>(), hamon::declval<T>())), "");

	return true;
}

template <typename Map, typename I, typename K, typename T, typename = void>
struct is_try_emplace_invocable
	: public hamon::false_type {};

template <typename Map, typename I, typename K, typename T>
struct is_try_emplace_invocable<Map, I, K, T, hamon::void_t<decltype(hamon::declval<Map>().try_emplace(hamon::declval<I>(), hamon::declval<K>(), hamon::declval<T>()))>>
	: public hamon::true_type {};

template <typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test2()
{
	using Map1 = hamon::unordered_map<TransparentKey, T>;
	using Map2 = hamon::unordered_map<TransparentKey, T, decltype(hamon::ranges::hash)>;
	using Map3 = hamon::unordered_map<TransparentKey, T, hamon::hash<TransparentKey>, hamon::equal_to<>>;
	using Map4 = hamon::unordered_map<TransparentKey, T, decltype(hamon::ranges::hash), hamon::equal_to<>>;

	static_assert(!is_try_emplace_invocable<Map1&, typename Map1::const_iterator, int, T>::value, "");
	static_assert(!is_try_emplace_invocable<Map2&, typename Map2::const_iterator, int, T>::value, "");
	static_assert(!is_try_emplace_invocable<Map3&, typename Map3::const_iterator, int, T>::value, "");
	static_assert( is_try_emplace_invocable<Map4&, typename Map4::const_iterator, int, T>::value, "");

	static_assert(!is_try_emplace_invocable<Map1 const&, typename Map1::const_iterator, int, T>::value, "");
	static_assert(!is_try_emplace_invocable<Map2 const&, typename Map2::const_iterator, int, T>::value, "");
	static_assert(!is_try_emplace_invocable<Map3 const&, typename Map3::const_iterator, int, T>::value, "");
	static_assert(!is_try_emplace_invocable<Map4 const&, typename Map4::const_iterator, int, T>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, TryEmplaceHintHeterogeneousTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2<int>());
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2<char>());
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2<float>());
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace try_emplace_hint_heterogeneous_test

}	// namespace hamon_unordered_map_test

#endif
