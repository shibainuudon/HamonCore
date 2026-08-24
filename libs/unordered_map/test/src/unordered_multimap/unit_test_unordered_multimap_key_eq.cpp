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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Map = hamon::unordered_multimap<Key, T, hamon::hash<Key>, TestEqualTo<Key>>;
	using Hasher = typename Map::hasher;
	using KeyEqual = typename Map::key_equal;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().key_eq()), KeyEqual>::value, "");
	static_assert( noexcept(hamon::declval<Map const&>().key_eq()), "");

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
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

}	// namespace key_eq_test

}	// namespace hamon_unordered_multimap_test
