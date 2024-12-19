/**
 *	@file	unit_test_map_op_assign_initializer_list.cpp
 *
 *	@brief	initializer_listを引数に取る代入演算子のテスト
 *
 *	map& operator=(initializer_list<value_type>);
 */

#include <hamon/map/map.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace op_assign_initializer_list_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::map<Key, T>;
	using ValueType = typename Map::value_type;
	using IL = std::initializer_list<ValueType>;

	static_assert( hamon::is_assignable<Map, IL>::value, "");
	static_assert(!hamon::is_nothrow_assignable<Map, IL>::value, "");
	static_assert(!hamon::is_trivially_assignable<Map, IL>::value, "");

	Map v1;
	VERIFY(v1.empty());

	{
		auto& r = (v1 =
		{
			{ Key{3}, T{10}},
			{ Key{1}, T{20}},
			{ Key{4}, T{30}},
		});
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 3);
		{
			auto it = v1.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{20}});
			VERIFY(*it++ == ValueType{Key{3}, T{10}});
			VERIFY(*it++ == ValueType{Key{4}, T{30}});
			VERIFY(it == v1.end());
		}
	}
	{
		auto& r = (v1 =
		{
			{ Key{1}, T{10}},
			{ Key{2}, T{20}},
			{ Key{1}, T{30}},
			{ Key{4}, T{40}},
			{ Key{1}, T{50}},
		});
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 3);
		{
			auto it = v1.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{10}});
			VERIFY(*it++ == ValueType{Key{2}, T{20}});
			VERIFY(*it++ == ValueType{Key{4}, T{40}});
			VERIFY(it == v1.end());
		}
	}
	{
		auto& r = (v1 = {});
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, OpAssignInitializerListTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace op_assign_initializer_list_test

}	// namespace hamon_map_test
