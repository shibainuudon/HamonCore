/**
 *	@file	unit_test_multimap_op_assign_initializer_list.cpp
 *
 *	@brief	initializer_listを引数に取る代入演算子のテスト
 *
 *	multimap& operator=(initializer_list<value_type>);
 */

#include <hamon/map/multimap.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace op_assign_initializer_list_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::multimap<Key, T>;
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
		VERIFY(v1.size() == 5);
		{
			auto it = v1.begin();
			VERIFY(*it++ == ValueType{Key{1}, T{10}});
			VERIFY(*it++ == ValueType{Key{1}, T{30}});
			VERIFY(*it++ == ValueType{Key{1}, T{50}});
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

GTEST_TEST(MultimapTest, OpAssignInitializerListTest)
{
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace op_assign_initializer_list_test

}	// namespace hamon_multimap_test
