/**
 *	@file	unit_test_unordered_map_hash_function.cpp
 *
 *	@brief	hash_function のテスト
 *
 *	constexpr hasher hash_function() const;
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

namespace hamon_unordered_map_test
{

namespace hash_function_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Map = hamon::unordered_map<Key, T, TestHash<Key>>;
	using Hasher = typename Map::hasher;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().hash_function()), Hasher>::value, "");
	static_assert( noexcept(hamon::declval<Map const&>().hash_function()), "");

	Hasher h1{42};
	Hasher h2{43};
	{
		Map v{17, h1};
		VERIFY(v.hash_function() == h1);
		VERIFY(v.hash_function() != h2);
	}
	{
		Map v{17, h2};
		VERIFY(v.hash_function() != h1);
		VERIFY(v.hash_function() == h2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, HashFunctionTest)
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

}	// namespace hash_function_test

}	// namespace hamon_unordered_map_test
