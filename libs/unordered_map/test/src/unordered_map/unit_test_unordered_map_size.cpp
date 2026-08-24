/**
 *	@file	unit_test_unordered_map_size.cpp
 *
 *	@brief	size のテスト
 *
 *	constexpr size_type size() const noexcept;
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_map_test
{

namespace size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Map = hamon::unordered_map<Key, T>;
	using SizeType  = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().size()), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().size()), SizeType>::value, "");
	static_assert(noexcept(hamon::declval<Map&>().size()), "");
	static_assert(noexcept(hamon::declval<Map const&>().size()), "");

	{
		Map v;
		VERIFY(v.size() == 0);
	}
	{
		Map const v;
		VERIFY(v.size() == 0);
	}
	{
		Map const v
		{
			{Key{2}, T{10}},
			{Key{3}, T{20}},
			{Key{1}, T{30}},
			{Key{1}, T{40}},
			{Key{2}, T{50}},
			{Key{3}, T{60}},
		};
		VERIFY(v.size() == 3);
	}
	{
		Map const v
		{
			{Key{2}, T{10}},
			{Key{3}, T{20}},
			{Key{1}, T{30}},
			{Key{4}, T{40}},
			{Key{5}, T{50}},
			{Key{3}, T{60}},
		};
		VERIFY(v.size() == 5);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, SizeTest)
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

}	// namespace size_test

}	// namespace hamon_unordered_map_test
