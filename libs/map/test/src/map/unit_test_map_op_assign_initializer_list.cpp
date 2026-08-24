/**
 *	@file	unit_test_map_op_assign_initializer_list.cpp
 *
 *	@brief	initializer_listを引数に取る代入演算子のテスト
 *
 *	map& operator=(initializer_list<value_type>);
 */

#include <hamon/map/map.hpp>
#include <hamon/initializer_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace op_assign_initializer_list_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Map = hamon::map<Key, T>;
	using ValueType = typename Map::value_type;
	using IL = hamon::initializer_list<ValueType>;

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
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));
}

}	// namespace op_assign_initializer_list_test

}	// namespace hamon_map_test
