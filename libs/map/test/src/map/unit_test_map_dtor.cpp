/**
 *	@file	unit_test_map_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	~map();
 */

#include <hamon/map/map.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace dtor_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

struct S
{
	static int s_dtor_count;

	int value;

	S(int v) : value(v)
	{
	}

	~S()
	{
		++s_dtor_count;
	}
};

int S::s_dtor_count = 0;

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::map<Key, T>;

	static_assert( hamon::is_destructible<Map>::value, "");
	static_assert( hamon::is_nothrow_destructible<Map>::value, "");
	static_assert(!hamon::is_trivially_destructible<Map>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, DtorTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	S::s_dtor_count = 0;
	{
		hamon::map<int, S> v;
	}
	EXPECT_EQ(0, S::s_dtor_count);

	S::s_dtor_count = 0;
	{
		hamon::map<int, S> v;

		v.emplace(0, 10);
		EXPECT_EQ(0, S::s_dtor_count);
	}
	EXPECT_EQ(1, S::s_dtor_count);

	S::s_dtor_count = 0;
	{
		hamon::map<int, S> v;
		v.emplace(1, 10);
		v.emplace(2, 15);
		v.emplace(3, 20);
		EXPECT_EQ(0, S::s_dtor_count);
	}
	EXPECT_EQ(3, S::s_dtor_count);
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace dtor_test

}	// namespace hamon_map_test
