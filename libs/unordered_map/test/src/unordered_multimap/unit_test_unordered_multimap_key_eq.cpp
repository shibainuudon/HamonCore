/**
 *	@file	unit_test_unordered_multimap_key_eq.cpp
 *
 *	@brief	key_eq のテスト
 *
 *	constexpr key_equal key_eq() const;
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

namespace hamon_unordered_multimap_test
{

namespace key_eq_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::unordered_multimap<Key, T, hamon::hash<Key>, TestEqualTo<Key>>;
	using Hasher = typename Map::hasher;
	using KeyEqual = typename Map::key_equal;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().key_eq()), KeyEqual>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	static_assert( noexcept(hamon::declval<Map const&>().key_eq()), "");
#endif

	KeyEqual pred1{42};
	KeyEqual pred2{43};
	{
		Map v{17, Hasher{}, pred1};
		VERIFY(v.key_eq() == pred1);
		VERIFY(v.key_eq() != pred2);
	}
	{
		Map v{17, Hasher{}, pred2};
		VERIFY(v.key_eq() != pred1);
		VERIFY(v.key_eq() == pred2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, KeyEqTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace key_eq_test

}	// namespace hamon_unordered_multimap_test
