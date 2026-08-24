/**
 *	@file	unit_test_unordered_map_op_assign_initializer_list.cpp
 *
 *	@brief	initializer_listを引数に取る代入演算子のテスト
 *
 *	constexpr unordered_map& operator=(initializer_list<value_type>);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/initializer_list.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_map_test
{

namespace op_assign_initializer_list_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Map = hamon::unordered_map<Key, T>;
	using ValueType = typename Map::value_type;

	static_assert( hamon::is_assignable<Map, hamon::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_nothrow_assignable<Map, hamon::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_trivially_assignable<Map, hamon::initializer_list<ValueType>>::value, "");

	Map v;
	v.max_load_factor(0.25f);
	VERIFY(v.empty());

	{
		auto& r = (v =
		{
			{ Key{1}, T{10} },
			{ Key{2}, T{20} },
			{ Key{3}, T{30} },
		});
		VERIFY(&r == &v);
	}
	VERIFY(v.size() == 3);
	VERIFY(v.load_factor() <= v.max_load_factor());
	VERIFY(v.at(Key{1}) == T{10});
	VERIFY(v.at(Key{2}) == T{20});
	VERIFY(v.at(Key{3}) == T{30});

	{
		auto& r = (v =
		{
			{ Key{1}, T{10} },
			{ Key{3}, T{20} },
			{ Key{5}, T{30} },
			{ Key{1}, T{40} },
			{ Key{5}, T{50} },
			{ Key{7}, T{60} },
			{ Key{3}, T{70} },
		});
		VERIFY(&r == &v);
	}
	VERIFY(v.size() == 4);
	VERIFY(v.load_factor() <= v.max_load_factor());
	VERIFY(v.at(Key{1}) == T{10});
	VERIFY(v.at(Key{3}) == T{20});
	VERIFY(v.at(Key{5}) == T{30});
	VERIFY(v.at(Key{7}) == T{60});

	{
		auto& r = (v =
		{
			{ Key{42}, T{99} },
		});
		VERIFY(&r == &v);
	}
	VERIFY(v.size() == 1);
	VERIFY(v.load_factor() <= v.max_load_factor());
	VERIFY(v.at(Key{42}) == T{99});

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, OpAssignInitializerListTest)
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

}	// namespace op_assign_initializer_list_test

}	// namespace hamon_unordered_map_test
