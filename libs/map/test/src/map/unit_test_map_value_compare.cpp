/**
 *	@file	unit_test_map_value_compare.cpp
 *
 *	@brief	value_compare のテスト
 *
 *	class value_compare {
 *	protected:
 *		Compare comp;
 *		value_compare(Compare c) : comp(c) {}
 *
 *	public:
 *		bool operator()(const value_type& x, const value_type& y) const {
 *			return comp(x.first, y.first);
 *		}
 *	};
 */

#include <hamon/map/map.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace value_compare_test
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
MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::map<Key, T>;
	using ValueCompare = typename Map::value_compare;
	using ValueType = typename Map::value_type;

	static_assert(!hamon::is_default_constructible<ValueCompare>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<ValueCompare>()(hamon::declval<ValueType>(), hamon::declval<ValueType>())),
		bool>::value, "");

	Map const m;
	ValueCompare const comp = m.value_comp();
	VERIFY(!comp(ValueType{Key{0}, T{10}}, ValueType{Key{0}, T{10}}));
	VERIFY( comp(ValueType{Key{0}, T{10}}, ValueType{Key{1}, T{10}}));
	VERIFY(!comp(ValueType{Key{1}, T{10}}, ValueType{Key{0}, T{10}}));
	VERIFY(!comp(ValueType{Key{1}, T{10}}, ValueType{Key{1}, T{10}}));

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, ValueCompareTest)
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
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace value_compare_test

}	// namespace hamon_map_test
