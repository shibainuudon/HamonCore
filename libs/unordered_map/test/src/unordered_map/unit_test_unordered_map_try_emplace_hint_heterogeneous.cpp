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

UNORDERED_MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::unordered_map<TransparentKey, float, decltype(hamon::ranges::hash), hamon::equal_to<>>;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().try_emplace(hamon::declval<ConstIterator>(), hamon::declval<int const&>(), hamon::declval<float>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().try_emplace(hamon::declval<ConstIterator>(), hamon::declval<int&&>(), hamon::declval<float>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().try_emplace(hamon::declval<ConstIterator>(), hamon::declval<int const&>(), hamon::declval<float>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().try_emplace(hamon::declval<ConstIterator>(), hamon::declval<int&&>(), hamon::declval<float>())), "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, TryEmplaceHintHeterogeneousTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace try_emplace_hint_heterogeneous_test

}	// namespace hamon_unordered_map_test

#endif
